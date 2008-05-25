/****************************************************************************
** Copyright (C) 2008 Petar Toushkov <peter dot toushkov at gmail.com>
** Copyright (C) 2008 Omer Bahri Gordebak <gordebak at gmail.com>
**
** Additional help, code and insights by:
** adamvert - from http://ubuntuforums.org/
** zebulon M - from http://ubuntuforums.org/
**
** Parts of the following code are from the Phrasis project:
**
** http://code.google.com/p/phrasis/
**
** and are
**
** Copyright (C) 2006 Jacob R Rideout <jacob@jacobrideout.net>
** All rights reserved.
**
** This file may be used under the terms of the GNU General Public
** License version 2.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/

#ifndef TEXTROOM_H
#define TEXTROOM_H

#include <QtGui>
 
#include "ui_textroom.h"

class QShortcut;
class QFileSystemWatcher;
class OptionsDialog;
class HelpDialog;
class SearchDialog;
class ProjectManager;

class TextRoom : public QWidget, public Ui::TextRoomMain
{
	Q_OBJECT
 
public:
	TextRoom(QWidget *parent = 0, Qt::WFlags f = 0 );
	void loadFile(const QString &fileName);

private slots:

	void open();
	bool save();
	bool saveAs();
	void about();
	void options();
	void projects();
	void newFile();
	void help();
	void insertDate();
	void insertTime();
	void find();
	void playSound(QString &filenm);
	void find_next();
	void find_previous();
	void sCursor();
	void togleFullScreen();
	void togleEscape();
	void indentFirstLines();
	void documentWasModified();	
	void getFileStatus();
	void readSettings();
	void alarmTime();
	void loadStyleSheet(const QString &fcolor, const QString &bcolor, const QString &scolor, const QString &sbcolor);

private:
	bool maybeSave();
	QString strippedName(const QString &fullFileName);
	void clearFormating(const QTextBlock& block);	
	void writeSettings();
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);

	HelpDialog *helpDialog;
	OptionsDialog *optionsDialog;
	SearchDialog *searchDialog;
	ProjectManager *projectManager;
	Ui::TextRoomMain ui;
	QString curFile;
	QString curDir;
	QString lastSearch;
	QString text;
	QString deadlinetext;
	QDate deadline;
	QDate today;
	QString editDate;
	int wordcount;
	QString wordcounttext;
	int alarm;
	int sentenceTally;
	QFileSystemWatcher* fw;
	bool optOpenLastFile;
	bool isSaveCursor;
	int editorWidth;
	int editorHeight;
	int numChanges;
	int prevLength;
	int parasold;
	int parasnew;
	int cPosition;
	bool ind;
	bool isAutoSave;
	bool isFlowMode;
	bool isSound;
	bool isIndent;
	bool isScrollBarVisible;

protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);	

};
 
 
#endif
