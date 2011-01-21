#ifndef SXREVFILE_H
#define SXREVFILE_H
/**
* History directory format:
* historyFile()
* |- 0003.rev
* |- 0002.rev
* |- 0001.rev
* |- 0000.rev
* [QMap<QString,QVariant> metainfo][QString log][QByteArray data]
*/

#include "sxfile.h"
#include "versionutils.h"

class QFile;
class QDir;

class SxVersionedFile : public SxFile
{
Q_OBJECT
public:
	SxVersionedFile( QObject *parent = 0);
	~SxVersionedFile();

	void setCurrentVersion( uint version );
	uint currentVersion( ) const;

	uint versions( QDir *history ) const;
	QString logMessage( uint revision ) const;
	QString logMessage( ) const;
	void setLogMessage( const QString &message );


	void setHistoryFileTemplate( const QString &historyFile );
	QString historyFileTempate( ) const;
	QString historyFile( const QString &file  ) const;

	virtual bool openFile( const QString &fileName );
	virtual bool saveFile( const QString &fileName );
	virtual bool initHistory( const QString &file );
	
	QMap<QString,QVariant> getHeadProps(QDir *history) const;
	QString makeNextVersionName( QDir *history ) const;
	QString makeVersionName( QDir *history, uint version ) const;

protected:

	virtual bool checkInHead( QFile *file, QDir *history );
	virtual bool checkoutHead( QFile *file, QDir *history );
	virtual bool checkoutVersion( QFile *file, QDir *history, uint version );
	virtual uint queryVersion( ) const;
	
	virtual QMap<QString,QVariant> metaInfo() const;
	bool getPatch( QFile *patch, QDir *history, uint version ) const;
	
private:
	QString m_historyFileTemplate;
	uint m_currentVersion;
	QString m_currentLogMessage;
	VersionUtils m_versionUtils;

};

#endif
