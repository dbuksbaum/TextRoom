#include "sxrevfile.h"
#include "getusername.h"
#include "versionutils.h"

#include <QFileInfo>
#include <QTemporaryFile>
#include <QVariant>
#include <QMap>
#include <QDateTime>
#include <QStringList>
#include <QBuffer>
#include <QDir>

#include <qdebug.h>

SxVersionedFile::SxVersionedFile( QObject *parent ) : SxFile ( parent )
{
	m_historyFileTemplate = "%{DIR}/%{FILE}.history";
	m_currentVersion = 0;
}

SxVersionedFile::~SxVersionedFile()
{

}

void SxVersionedFile::setCurrentVersion( uint version )
{
	m_currentVersion = version;
}

uint SxVersionedFile::currentVersion( ) const
{
	return m_currentVersion;
}

uint SxVersionedFile::versions(  QDir *history ) const
{
	QStringList filter;
	filter << "*.rev";
	return history->entryList(filter).count();
}

QString SxVersionedFile::logMessage( uint revision ) const
{
	return QString();
}

void SxVersionedFile::setHistoryFileTemplate( const QString &historyFile )
{
	m_historyFileTemplate = historyFile;
}

QString SxVersionedFile::historyFileTempate( ) const
{
	return m_historyFileTemplate;
}

QString SxVersionedFile::logMessage( ) const
{
	return m_currentLogMessage;
}

void SxVersionedFile::setLogMessage( const QString &message )
{
	m_currentLogMessage = message;
}

QString SxVersionedFile::historyFile( const QString &file ) const
{
	QMap<QString,QString> subMap = filePropertyMap( file );
	QString returnFileName = m_historyFileTemplate;
	QStringList keys = subMap.keys();
	foreach( QString key, keys )
		returnFileName.replace("%{" + key + "}", subMap[key] );

qDebug() << "History:" << file << returnFileName;
	return returnFileName;
}

uint SxVersionedFile::queryVersion( ) const
{
	return 0;
}

QMap<QString,QVariant> SxVersionedFile::metaInfo() const
{
	//[QMap<QString,QVariant> metainfo][QByteArray data]
	QMap<QString,QVariant> propMap;
	propMap["USER"] = currentUserName();
	propMap["TIMESTAMP"] = QDateTime::currentDateTime();
	propMap["LOG"] = "Initial version";
	return propMap;
}

bool SxVersionedFile::initHistory( const QString &file  )
{
	QDir history( historyFile( file ) );
	if( history.exists() )
		return true;

	if( !history.mkpath( historyFile( file ) ) )
	{
		return false;
	}

	// Read source file, and copy it into the first revision.
	QFile fileIn( file );
	if( !fileIn.open(QIODevice::ReadOnly) )
		return false;

	bool result = checkInHead( &fileIn, &history );
	fileIn.close();
	return result;
}

QMap<QString,QVariant> SxVersionedFile::getHeadProps(QDir *history) const
{
	QMap<QString,QVariant> props;
	
	if( !history->exists() )
		return props;
	
	QFile revFile( makeVersionName( history, 0) );
	if( !revFile.open(QIODevice::ReadOnly) )
		return props;
	
	QDataStream inputStream( &revFile );
	inputStream >> props;
	return props;
}

bool SxVersionedFile::checkoutHead( QFile *file, QDir *history )
{
	QMap<QString,QVariant> props;
	QByteArray data;

	if( !history->exists() )
		return false;

	QFile revFile( makeVersionName( history, 0) );
	if( !revFile.open(QIODevice::ReadOnly) )
		return false;

	QDataStream outputStream( file );
	QDataStream inputStream( &revFile );
	inputStream >> props >> data;
	file->seek(0);
	file->write( data );
	file->seek(0);

	revFile.close();
	return true;
}

QString SxVersionedFile::makeVersionName( QDir *history, uint version ) const
{
	QString revName;
	if( version == 0 )
		revName = "head.rev";
	else
	{
		revName = QString::number( version ) + ".rev";
		revName = revName.rightJustified(8,'0');
	}
	return history->absolutePath() + "/" + revName;
}

QString SxVersionedFile::makeNextVersionName( QDir *history ) const
{
	return makeVersionName( history, versions( history ) );
}

bool SxVersionedFile::checkInHead( QFile *file, QDir *history)
{
	QMap<QString,QVariant> props;
	QByteArray data;
	
	
	QFile revFile( makeVersionName( history, 0) );

	
	if( revFile.exists () )
	{
		// Build patch
		if( !revFile.open(QIODevice::ReadWrite) )
			return false;
		// Diff current file and revFile.  save patch as rev + 1;
		qDebug() << "Diff" << revFile.fileName();
		QTemporaryFile patch;
		patch.open();
		
		m_versionUtils.diffQFiles( file, &revFile, &patch );

		QMap<QString,QVariant> props = getHeadProps( history);
		QString revName = makeNextVersionName( history );
		qDebug() << "Write to" << revName;
		
		QFile rev( revName );
		if( !rev.open(QIODevice::WriteOnly) )
			return false;
		QDataStream outputStream( &rev );
		patch.seek(0);
		outputStream << props << patch.readAll();
		rev.close();
		patch.close();
		revFile.close();
	}

	if( !revFile.open(QIODevice::ReadWrite) )
		return false;
	QDataStream outputStream( &revFile );
	quint64 origPos = file->pos();
	file->seek(0);
	outputStream << metaInfo() << file->readAll();
	file->seek(origPos);
	revFile.close();
	return true;

}

bool SxVersionedFile::getPatch( QFile *patch, QDir *history, uint version ) const
{
	QFile revFile( makeVersionName( history, version ) );
	if( revFile.open(QIODevice::ReadOnly) )
	{
		QMap<QString,QVariant> props;
		QByteArray data;
		QDataStream revStream( &revFile );
		
		revStream >> props >> data;
		patch->seek(0);
		patch->write( data );
		patch->seek(0);
		revFile.close();

		return true;
	}
	else
	{
		qDebug() << "failed: " << revFile.fileName();
		return false;
	}
}

bool SxVersionedFile::checkoutVersion( QFile *file, QDir *history, uint version )
{
	if( version == 0 )
		return checkoutHead( file, history );
	

	if( !checkoutHead( file, history ) )
		return false;
	file->close();
	
	for( uint idx = versions( history ) - 1; idx >= version; --idx )
	{
		QString patch = makeVersionName( history, idx );
		QTemporaryFile patchFile;
		QTemporaryFile destFile;
		
		
		patchFile.open();
		destFile.open();

		if( !getPatch( &patchFile, history, idx ) )
		{
			qDebug() << "Failed to get patch for" << idx;
			return false;
		}

// 		patchFile.close();
// 		destFile.close();
		
		
		if( m_versionUtils.patchFile( file->fileName(), patchFile.fileName(), destFile.fileName()))
		{
			qDebug() << "Patch " << patchFile.fileName() << destFile.fileName() << file->fileName();
			// copy contents of patchFile into file.
			QFile::remove( file->fileName() );
			if( !QFile::copy( destFile.fileName(), file->fileName() ) )
				qDebug() << "Failed copy" << destFile.fileName() << file->fileName();
			qDebug() << "Dest file" << destFile.readAll();
		}
		else
		{
			qDebug() << "Failed to patch" << file->fileName();
			return false;
		}
		
	}

	return true;
}

bool SxVersionedFile::openFile( const QString &fileName )
{
	if( !initHistory( fileName ) )
	{
		return false;
	}

	QTemporaryFile openFile;
	bool result = false;
	if (openFile.open())
	{
		QDir history( historyFile(fileName) );
		result = checkoutVersion( &openFile, &history, queryVersion( ) );
		
		if( result )
		{
			if( m_versionUtils.filesIdentical( fileName, openFile.fileName() ) )
			{
				return SxFile::openFile( fileName );
			}
			else
			{
				
				QFile::remove(fileName);
				if( !openFile.copy(fileName) )
					return false;

				
				return SxFile::openFile( fileName );
			}
		}
		else
			return false;
	}
	else
		return false;

}

bool SxVersionedFile::saveFile( const QString &fileName )
{
	if( !SxFile::saveFile(fileName) )
		return false;
	
	if( !initHistory( fileName ) )
		return false;
	QFile savedFile( fileName );
	QDir history( historyFile( fileName  ) );
	if( savedFile.open(QIODevice::ReadOnly) )
		return checkInHead( &savedFile, &history );
	else
		return false;
}
