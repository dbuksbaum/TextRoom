/****************************************************************************
** Copyright (C) 2008 Petar Toushkov <peter dot toushkov at gmail.com>
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
 
class TextRoom : public QWidget, public Ui::TextRoomMain
{
	Q_OBJECT
 
public:
	TextRoom(QWidget *parent = 0, Qt::WFlags f = 0 );
 
private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void about();
	void options();
	void help();
	void togleFullScreen();
	void togleEscape();
	void indentFirstLines();
	void setStatsLabelText(int position, int charsRemoved, int charsAdded);
	void documentWasModified();	
	void cramStatsLabel();
	void dateTimeStatsLabel();
	void getFileStatus();
	void readSettings();
	void loadStyleSheet(const QString &sheetName,
		const QString &fcolor,
		const QString &bcolor,
		const QString &scolor);

private:
	bool maybeSave();
	void loadFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	QString strippedName(const QString &fullFileName);
	void clearFormating(const QTextBlock& block);	
	void writeSettings();

	HelpDialog *helpDialog;
	OptionsDialog *optionsDialog;
	Ui::TextRoomMain ui;
	QString curFile;
	QString curDir;
	int sentenceTally;
	QFileSystemWatcher* fw;
	bool optOpenLastFile;
	int numChanges;
	int prevLength;
	bool isAutoSave;
	bool isFlowMode;

protected:
	void closeEvent(QCloseEvent *event);	
};
 
 
#endif
