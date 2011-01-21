/*
    Copyright (C) SourceXtreme, Inc. <oss@sourcextreme.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "sxfile.h"
#ifdef WITH_GETUSER
#include "getusername.h"
#endif
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QMenu>
#include <QAction>
#include <QSettings>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>

const QString baseExportFileTemplate = "%{FILE}.%1";
const QString baseExportAbsFileTemplate = "%{DIR}/%{FILE}.%1";

SxFile::SxFile( QObject *parent ) : QObject(parent), m_recentFilesMenu(0)
{

#ifdef Q_OS_WIN32
	m_backupFileTemplate = "%{DIR}/%{FILE}.bak";
	m_defaultPathTemplate = "%{HOME}/My Documents";
	m_autosaveFileTemplate = "%{DIR}/%{FILE}.autosave";
#else
	m_autosaveFileTemplate = "%{DIR}/.%{FILE}~";
	m_defaultPathTemplate = "%{HOME}/Documents";
	m_backupFileTemplate = "%{DIR}/%{FILE}.backup";
#endif
	QSettings settings;
	settings.beginGroup("FileManager");
	m_backupOnSave = settings.value("BackupOnSave", false).value<bool>();
	m_autoSaveTimeout = settings.value("AutoSaveInterval", 0).value<int>();
	settings.endGroup();

	setupAutoSaveTimer();
	setupRecentFileActions();
	updateRecentFileActions();

	setModified(false);
}

void SxFile::setupAutoSaveTimer()
{
	m_autoSaveTimer = new QTimer(this);
	connect( m_autoSaveTimer, SIGNAL(timeout()), SLOT(slotAutoSave()));

	setAutoSaveTimeout( m_autoSaveTimeout );
}

SxFile::~SxFile()
{
	removeAutoSaveFile();
	delete m_recentFilesMenu;
}

QString SxFile::buildFileFilter() const
{
	QString fieldTemplate = "%1 (*.%2)";
	QStringList filter;
	QStringList formats = m_supportedFiles.keys();
	foreach( QString format, formats )
		filter << fieldTemplate.arg(m_supportedFiles[format]).arg(format);
	filter << tr("All Files (*.*)");
	return filter.join(";;");
}

QString SxFile::openFileName() const
{
	return QFileDialog::getOpenFileName( QApplication::activeWindow(), tr("Select load file..."), currentPath(), buildFileFilter() );
}

QString SxFile::saveFileName() const
{
	return QFileDialog::getSaveFileName( QApplication::activeWindow(), tr("Select save file..."), currentPath(), buildFileFilter());
}


void SxFile::slotOpenFile()
{
	if( !queryCloseCurrentFile() )
		return;
	removeAutoSaveFile();
	QString newFileName = openFileName();
	if( newFileName.isEmpty() )
		return;
	doOpenFile( newFileName );
}

void SxFile::slotSaveFile()
{
	QString startDir = currentPath();
	QString fileName;

	if( currentFile().isEmpty() )
	{
		fileName = saveFileName();
		if( fileName.isEmpty() )
			return;
	}
	else
	{
		fileName = currentFile();
	}

	backupFile();
	doSaveFile( setDefaultExtension( fileName ) );

}

void SxFile::slotSaveAsFile( )
{
	QString startDir = currentFile();
	QString fileName = saveFileName();
	if( fileName.isEmpty() )
		return;

	doSaveFile( setDefaultExtension(fileName) );
}

void SxFile::slotNewFile()
{
	if( !queryCloseCurrentFile() )
		return;
	initData();
	removeAutoSaveFile();
	setCurrentFile( QString() );
        setModified( false );

	emit status( tr("Ready..") );
	emit fileLoaded( tr("Untitled") );
}

void SxFile::slotReloadFile()
{
	if( currentFile().isEmpty() )
		return;
	if( !queryCloseCurrentFile() )
		return;
	removeAutoSaveFile();
	doOpenFile( currentFile() );
}

QIODevice *SxFile::getOpenFile( const QString &fileName )
{
	QFile *openFile = new QFile(fileName, this);
	if( openFile->open(QIODevice::ReadOnly) )
		return openFile;
	emit status( tr("Error \"%1\" opening %2").arg(openFile->errorString()).arg(fileName) );
	delete openFile;
	return 0;
}

bool SxFile::openFile( const QString &fileName )
{
	QIODevice *openFile = getOpenFile(fileName);
	if( 0 == openFile )
		return false;

	bool result = loadData( openFile );
	delete openFile;
	return result;
}

QIODevice *SxFile::getSaveFile( const QString &fileName )
{
	QFile *saveFile = new QFile(fileName, this);
	if( saveFile->open(QIODevice::WriteOnly) )
		return saveFile;
	emit status( tr("Error \"%1\" saving %2").arg(saveFile->errorString()).arg(fileName) );
	delete saveFile;
	return 0;
}

bool SxFile::saveFile( const QString &fileName )
{
	QIODevice *saveFile = getSaveFile(fileName);
	if( 0 == saveFile  )
		return false;

	bool result = saveData( saveFile );
	delete saveFile;;
	return result;
}

bool SxFile::loadData( QIODevice *iodevice )
{
	Q_UNUSED(iodevice);
	return false;
}

bool SxFile::saveData( QIODevice *iodevice )
{
	Q_UNUSED(iodevice);
	return false;
}

void SxFile::initData( )
{

}

QString SxFile::currentFile( ) const
{
	return m_currentFile;
}

void SxFile::setCurrentFile( const QString &fileName )
{
	m_currentFile = fileName;
}

QMap<QString,QString> SxFile::supportedFiles() const
{
	return m_supportedFiles;
}

void SxFile::setSupportedFiles( QMap<QString,QString> &supportedFiles )
{
	m_supportedFiles = supportedFiles;
}

bool SxFile::backupOnSave() const
{
	return m_backupOnSave;
}

void SxFile::setBackupOnSave( bool save )
{
	m_backupOnSave = save;
}

QString SxFile::currentPath( ) const
{
	if( currentFile().isEmpty() )
		return defaultPath();
	QFileInfo info(currentFile());
	return info.absolutePath();
}

QString SxFile::currentBaseName( ) const
{
	if( currentFile().isEmpty() )
		return QString();

	QFileInfo info( currentFile() );
	return info.baseName();
}

QMenu *SxFile::recentFileMenu(   ) const
{
	return m_recentFilesMenu;
}

void SxFile::setupRecentFileActions()
{
	if( m_recentFilesMenu == 0)
		m_recentFilesMenu = new QMenu(tr("Open Recent..."));

	qDeleteAll( m_recentFiles );
	m_recentFiles.clear();

	QSettings settings;
	settings.beginGroup("FileManager");
	int maxFiles = settings.value("MaximumRecentFiles", 5).value<int>();
	settings.endGroup();

	for (int i = 0; i < maxFiles; ++i)
	{
		QAction *action = m_recentFilesMenu->addAction( QString() );
		action->setVisible(false);
		connect(action, SIGNAL(triggered()), this, SLOT(slotOpenRecentFile()));
		m_recentFiles << action;
	}
}

void SxFile::slotOpenRecentFile()
{
	if( !queryCloseCurrentFile() )
		return;
	removeAutoSaveFile();
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)
	{
		QString newFileName = action->data().value<QString>();
		doOpenFile( newFileName );
	}
}

void SxFile::updateRecentFileActions()
{
	QSettings settings;
	settings.beginGroup("FileManager");
	QStringList files = settings.value("RecentFiles").value<QStringList>();

	if( !currentFile().isEmpty() )
	{
		files.removeAll( currentFile() );
		files.prepend( currentFile() );
		while (files.size() > m_recentFiles.size())
			files.removeLast();
		settings.setValue("RecentFiles", files);
		settings.endGroup();
	}

	int count = qMin( files.size(), m_recentFiles.size() );

	for (int idx = 0; idx < count; ++idx)
	{
		QString text = tr("&%1 %2").arg(idx + 1).arg( QFileInfo( files.at(idx)).fileName() );
		m_recentFiles.at(idx)->setText(text);
		m_recentFiles.at(idx)->setData(files.at(idx));
		m_recentFiles.at(idx)->setVisible(true);
	}

	for (int idx = count; idx < m_recentFiles.size(); ++idx)
		m_recentFiles.at(idx)->setVisible(false);
}

int SxFile::autoSaveTimeout( ) const
{
	return m_autoSaveTimeout;
}

void SxFile::setAutoSaveTimeout( int timeout )
{
	m_autoSaveTimeout = timeout;
	if( m_autoSaveTimeout != 0)
	{
		m_autoSaveTimer->setInterval( m_autoSaveTimeout * 60000); // minutes
		m_autoSaveTimer->start();
	}
	else
	{
		m_autoSaveTimer->stop();
	}
}

void SxFile::slotAutoSave()
{
	if( currentFile().isEmpty() )
		return;
  if( !modified() )
		return;

	saveFile( autosaveFileName( ) );
}

void SxFile::removeAutoSaveFile()
{
	if( !currentFile().isEmpty() )
		QFile::remove( autosaveFileName( ) );
	setAutoSaveTimeout(m_autoSaveTimeout);
}

void SxFile::dataChanged()
{
  setModified(true);
}

bool SxFile::queryCloseCurrentFile()
{
  if( modified() == false )
		return true;

	int result = QMessageBox::warning ( QApplication::activeWindow(),
	                                     tr("WARNING: You have unsaved data"),
	                                     tr("Do you wish to save the current document?"),
	                                     QMessageBox::Cancel|
	                                     QMessageBox::Save|
	                                     QMessageBox::Discard);
	if( result == QMessageBox::Cancel)
		return false;
	else if( result == QMessageBox::Save )
	{
		slotSaveFile();
  	if( modified() == false )
			return true;
		else
			return false;
	}
	else if( result == QMessageBox::Discard )
		return true;
	return false;
}

void SxFile::backupFile()
{
	if( m_backupOnSave && !currentFile().isEmpty() )
	{
		QString dest = backupFileName();
		QFile::remove( dest );
		QFile::copy( currentFile(), dest );
	}
}

void SxFile::doOpenFile( const QString &fileName )
{
	QString newFileName = fileName;
	bool autoSaveFile = checkForAutoSaveFile( fileName );
	if( autoSaveFile )
		newFileName = autosaveFileName( );

	if( openFile( newFileName ))
	{
		setCurrentFile( fileName );
		if( autoSaveFile )
  		setModified(true);
		else
  		setModified(false);
  		emit fileModified( modified() );
		emit fileLoaded( fileName );
		emit status( tr("Loaded %1").arg( fileName ) );
		updateRecentFileActions();
	}
	else
	{
		slotNewFile();
	}
}

QString SxFile::setDefaultExtension( const QString &fileName ) const
{
	QFileInfo info( fileName );
	if( info.suffix().isEmpty() && !m_supportedFiles.empty() )
		return fileName + "." + m_supportedFiles.keys().first();
	else
		return fileName;
}

void SxFile::doSaveFile(  const QString &saveFileName )
{
	if( saveFile( saveFileName ) )
	{
		removeAutoSaveFile();
		setCurrentFile( saveFileName );
		emit fileSaved( saveFileName );
		emit status( tr("Saved %1").arg( saveFileName ) );
		setModified(false);
		emit fileModified( modified() );
		updateRecentFileActions();
	}
}

bool SxFile::checkForAutoSaveFile( const QString &fileName )
{
	if( m_autoSaveTimeout == 0 )
		return false;

	QFileInfo fileNameInfo( fileName );
	QFileInfo autoBackupFileNameInfo( autosaveFileName( ) );

	if( autoBackupFileNameInfo.exists() )
	{
		if( fileNameInfo.lastModified().secsTo( autoBackupFileNameInfo.lastModified() ) > 0 )
		{
			int result = QMessageBox::question ( QApplication::activeWindow(),
					tr("WARNING: An autosave document exsits..."),
					tr("There is an autosaved document that is more recent than the saved version of this file.  Would you like to open the autosaved version instead?"),
					QMessageBox::Yes,
					QMessageBox::No);
			if( result == QMessageBox::Yes)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;

}

QString SxFile::generateSystemFileName( const QString &fileName, const QString &type ) const
{
	QFileInfo fileNameInfo( fileName );
	return fileNameInfo.absolutePath() + "/" + fileNameInfo.baseName() + "." + type;
}

void SxFile::setBackupFileTemplate( const QString &fileTemplate )
{
	m_backupFileTemplate = fileTemplate;
}

QString SxFile::backupFileTemplate( ) const
{
	return m_backupFileTemplate;
}


QString SxFile::expandTemplate( const QString &source ) const
{
	QMap<QString,QString> subMap;
	if( m_currentFile.isEmpty() )
		subMap = filePropertyMap( "untitled" );
	else
		subMap = filePropertyMap( m_currentFile );
	QString returnFileName = source;
	QStringList keys = subMap.keys();
	foreach( QString key, keys )
		returnFileName.replace("%{" + key + "}", subMap[key] );

	return returnFileName;
}

QMap<QString,QString> SxFile::filePropertyMap( const QString &file ) const
{
	QFileInfo fileInfo( file );
	QMap<QString,QString> subMap;
	subMap["CURRENT_DATETIME"] = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
	subMap["CURRENT_DATE"] = QDateTime::currentDateTime().toString("yyyyMMdd");
	subMap["CURRENT_TIME"] = QDateTime::currentDateTime().toString("hhmmss");
	subMap["FILE_DATETIME"] = fileInfo.lastModified().toString("yyyyMMddhhmmss");
	subMap["FILE_DATE"] = fileInfo.lastModified().toString("yyyyMMdd");
	subMap["FILE_TIME"] = fileInfo.lastModified().toString("hhmmss");
	subMap["FILE"] = fileInfo.baseName();
	subMap["DIR"] = fileInfo.absolutePath();
	subMap["SUFFIX"] = fileInfo.suffix();
#ifdef WITH_GETUSER
	subMap["USERNAME"] = currentUserName();
#endif
	subMap["OWNER"] = fileInfo.owner();
	subMap["HOME"] = QDir::homePath();
	subMap["TEMP"] = QDir::tempPath();
	subMap["PWD"] = QDir::currentPath();
	subMap["APPDIR"] = QCoreApplication::applicationDirPath();
	subMap["ORGNAME"] = QCoreApplication::organizationName();
	subMap["APPNAME"] = QCoreApplication::applicationName();
	return subMap;
}

QString SxFile::backupFileName( ) const
{
	return expandTemplate( m_backupFileTemplate );
}

void SxFile::setAutosaveFileTemplate( const QString &fileTemplate )
{
	m_autosaveFileTemplate = fileTemplate;
}

QString SxFile::autosaveFileTemplate( ) const
{
	return m_autosaveFileTemplate;
}

QString SxFile::autosaveFileName( ) const
{
	return expandTemplate( m_autosaveFileTemplate );
}

void SxFile::setDefaultPathTemplate( const QString &pathTemplate )
{
	m_defaultPathTemplate = pathTemplate;
}

QString SxFile::defaultPathTemplate( ) const
{
	return m_defaultPathTemplate;
}

QString SxFile::defaultPath() const
{
	return expandTemplate( m_defaultPathTemplate );
}

bool SxFile::modified() const
{
  return m_modified;
}

void SxFile::setModified( bool value )
{
  if( value )
  {
    m_modified = true;
    emit fileModified( true );
  }
  else
    m_modified = false;
}

QString SxFile::generateFileName( const QString & extension ) const
{
	return expandTemplate( baseExportFileTemplate ).arg(extension);
}

QString SxFile::generateFilePath( const QString & extension ) const
{
	return expandTemplate( baseExportAbsFileTemplate ).arg(extension);
}

QStringList  SxFile::recentFileList( ) const
{
        QSettings settings;
        settings.beginGroup("FileManager");
        return settings.value("RecentFiles").value<QStringList>();
}

void SxFile::slotOpenFileByName( const QString & fileName )
{
	doOpenFile( fileName );
}
