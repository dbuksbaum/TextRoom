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

#ifndef SXFILE_H
#define SXFILE_H

#include <QObject>
#include <QMap>
#include <QList>

class QIODevice;
class QAction;
class QMenu;
class QTimer;
/**
* This is a File class that handles quite a few File operations that are commonly used in desktop applications.
* Currently the following operations are provided:
* New file, Save file, Open file, Save as file, Backup old version of a file on save, Autosave after a timeout, and Autosave recovery.
*
*/
class SxFile : public QObject
{
Q_OBJECT
Q_CLASSINFO("license", "LGPL")
Q_PROPERTY(QString currentFile READ currentFile )
Q_PROPERTY(QString currentPath READ currentPath )
Q_PROPERTY(QString currentBaseName READ currentBaseName )
Q_PROPERTY(QString backupFileName READ backupFileName )
Q_PROPERTY(QString autosaveFileName READ autosaveFileName )
Q_PROPERTY(QString defaultPath READ defaultPath )
Q_PROPERTY(bool backupOnSave READ backupOnSave WRITE setBackupOnSave )
Q_PROPERTY(int autoSaveTimeout READ autoSaveTimeout WRITE setAutoSaveTimeout )
Q_PROPERTY(QString backupFileTemplate READ backupFileTemplate WRITE setBackupFileTemplate )
Q_PROPERTY(QString autosaveFileTemplate READ autosaveFileTemplate WRITE setAutosaveFileTemplate )
Q_PROPERTY(QString defaultPathTemplate READ defaultPathTemplate WRITE setDefaultPathTemplate )
Q_PROPERTY(bool modified READ modified WRITE setModified )

public:
	SxFile( QObject *parent = 0);
	~SxFile();

public slots:
	/**
	 * Call the FileOpen dialog, and open a selected file.
	 */
	void slotOpenFile();

	/**
	 *    Open a file by name.
	 */
	void slotOpenFileByName( const QString &fileName );

	/**
	 * Call the FileSave dialog if the document is unnamed, otherwise
	 * save the current file without user interaction.
	 */
	void slotSaveFile();

	/**
	 * Call the FileSave dialog and set the current document to
	 * the saved file name.
	 */
	void slotSaveAsFile();

	/**
	 * Reset the current file name, and calls the @ref initData() method.
	 */
	void slotNewFile();

	/**
	* Restore the current file data to the version on disk.
	*/
	void slotReloadFile();

	/**
	 * Notify the file that the data has been changed and is now out
	 * of sync with what is on the disk.
	 */
	void dataChanged();

	/**
	 * Update the state of the file if it is dirty or not.
	 */
	void setModified( bool modified );

public:
	/**
	 * Open the file fileName and call @ref loadData() with its QFile pointer. This will update the @ref currentFile().
	 */
	virtual bool openFile( const QString &fileName );
	/**
	 * Opens the file fileName for saving and calls @ref saveData() with its QFile pointer. This method will not update the @ref currentFile().
	 */
	virtual bool saveFile( const QString &fileName );

	/**
	 * Returns the full path to the current file that is handled by this object.
	 */
	QString currentFile( ) const;

	/**
	 * Returns the current path that the file dialogs will appear.
	 */
	QString currentPath( ) const;


	/**
	 *    Generates a new file name based off of the current file name.  This is useful when you wish to generate export files and need a common base name with a different extension.  This method can use all macros supported by @ref filePropertyMap if you wish to make dynamic file names.
	 * @param extention The new file extension
	 * @return The new file name.
	 */
	QString generateFileName( const QString &extention ) const;

	/**
	 *    This is similar to the generateFileName method except for it provides a full absolute path to the new file.
	 * @param extension The new file extension
	 * @return The new file name with absolute path.
	 */
	QString generateFilePath( const QString &extension ) const;

	/**
	 * Returns the base name of the current file.
	 */
	QString currentBaseName( ) const;

	QMap<QString,QString> supportedFiles() const;
	void setSupportedFiles( QMap<QString,QString> &supportedFiles );

	bool backupOnSave() const;
	void setBackupOnSave( bool save );

	/**
	 * Set the time interval in minutes that a backup will be performed.
	 */
	int autoSaveTimeout( ) const;
	void setAutoSaveTimeout( int timeout );

	/**
	 * Returns a QMenu with all the recent files handled by this object.
	 * This will save the file list in the "FileManager" group under the
	 * "RecentFiles" key.  When a file is selected on the menu, it will be
	 * opened as if it where selected in the @ref slotOpenFile() file dialog.
	 */
	QMenu *recentFileMenu( ) const;

	QStringList recentFileList( ) const;

	/**
	 * If the current file is modified should we save it before continuing.
	 */
	bool queryCloseCurrentFile();


	/**
	* Set the backup file template.  The following macros can be used to
	* format the saved file's name.  This template can use the properties
	* supplied by @ref filePropertyMap
	*/
	void setBackupFileTemplate( const QString &fileTemplate );
	QString backupFileTemplate( ) const;
	QString backupFileName( ) const;

	/**
	* Set the autosave file template.  The following macros can be used to
	* format the saved file's name.  This template can use the properties
	* supplied by @ref filePropertyMap.  NOTE: since the date and time properties
	* can change between saves they may defeat the autorecovery option.
	*/
	void setAutosaveFileTemplate( const QString &fileTemplate );
	QString autosaveFileTemplate( ) const;
	QString autosaveFileName( ) const;

	/**
	* Set the default path template. This path will be used when the user
	* tries to open a file the first time.  The following macros can be used to
	* format the saved file's name.  This template can use the properties
	* supplied by @ref filePropertyMap.
	*/
	void setDefaultPathTemplate( const QString &pathTemplate );
	QString defaultPathTemplate( ) const;
	QString defaultPath() const;

	/**
	* Get the current modified state of the data file.
	*/
	bool modified() const;
protected:
	/**
	 * Implement this method to populate your internal data with the
	 * contents of the QIODevice.  The default implementation returns false.
	 * This method is called by @ref openFile().
	 */
	virtual bool loadData( QIODevice *iodevice );
	/**
	 * Implement this method to save your internal data to the QIODevice.
	 * default implementation of this does nothing. This method is called by @ref saveFile().
	 */
	virtual bool saveData( QIODevice *iodevice );
	/**
	 * Implement this to reset your internal data.  The default implementation
	 * does nothing.  This method is called by @ref slotNewFile().
	 */
	virtual void initData( );

	/**
	* Property map for the current file.  These properties are used in @ref setBackupFileTemplate
	* Properties:
	* @li %{CURRENT_DATETIME} - the current date and time in ISO format.
	* @li %{CURRENT_DATE} - the current date in ISO format.
	* @li %{CURRENT_TIME} - the current time in ISO format.
	* @li %{FILE_DATETIME} - the file's last modified date and time in ISO format.
	* @li %{FILE_DATE} - the file's last modified date in ISO format.
	* @li %{FILE_TIME} - the file's last modified time in ISO format.
	* @li %{FILE} - current files name as returned by @ref QFile::baseName.
	* @li %{DIR} - the absolute path to the current file.
	* @li %{SUFFIX} - suffix of the current file.
	* @li %{USERNAME} - the current username of the person running the program.
	* @li %{OWNER} - the username of the last person to modify the file.
	* @li %{TEMP} - the user's temporary directory.
	* @li %{HOME} - the user's home directory.
	* @li %{PWD} - the current working directory.
	* @li %{APPDIR} - the directory that the application was launched from.
	* @li %{ORGNAME} - the organisational name of the application.
	* @li %{APPNAME} - the application name.
	*/
	virtual QMap<QString,QString> filePropertyMap(const QString &file) const;
	/**
	* Expand a string that contains properties from @ref filePropertyMap.
	*/
	QString expandTemplate( const QString &source ) const;
	virtual void backupFile();
	void setCurrentFile( const QString &fileName );
	void updateRecentFileActions();

	virtual QString openFileName() const;
	virtual QString saveFileName() const;
	virtual QIODevice *getOpenFile( const QString &fileName );
	virtual QIODevice *getSaveFile( const QString &fileName );
	virtual QString setDefaultExtension( const QString &fileName ) const;
signals:
	void fileLoaded( const QString &fileName ) const;
	void fileSaved( const QString &fileName ) const;
	void status( const QString &statusMsg ) const;
	void fileModified( bool state ) const;

private slots:
	void slotOpenRecentFile();
	void slotAutoSave();

private:
	void setupRecentFileActions();
	void setupAutoSaveTimer();
	QString buildFileFilter() const;
	void removeAutoSaveFile();
	bool checkForAutoSaveFile( const QString &fileName );
	void doSaveFile(  const QString &saveFileName );
	void doOpenFile( const QString &fileName );

	QString generateSystemFileName( const QString &fileName, const QString &type ) const;

	QString m_currentFile;
	QString m_defaultPath;

	QMap<QString,QString> m_supportedFiles;

	QList<QAction*> m_recentFiles;
	QMenu *m_recentFilesMenu;

	bool m_backupOnSave;

	QTimer *m_autoSaveTimer;
	int m_autoSaveTimeout;

	bool m_modified;

	QString m_backupFileTemplate;
	QString m_autosaveFileTemplate;
	QString m_defaultPathTemplate;
};

#endif
