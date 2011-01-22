/****************************************************************************
** Copyright (C) 2008 Petar Toushkov <peter dot toushkov at gmail.com>
** Copyright (C) 2008 Omer Bahri Gordebak <gordebak at gmail.com>
**
** Additional help, code and insights by:
** adamvert - from http://ubuntuforums.org/
** zebulon M - from http://ubuntuforums.org/
**
** Artwork by Edward Solodukhin <arch1000@gmail.com>
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
class SelectFont;
class AboutDialog;
class ScratchDialog;
class Hunspell;
class MiniFlo;
class GetAWord;
class MusicRoom;
class GoogleDocsDialog;
struct Mix_Chunk;

class TextRoom : public QWidget, public Ui::TextRoomMain
{
	Q_OBJECT
 
public:
	TextRoom(QWidget *parent = 0, Qt::WFlags f = 0 );
#ifdef Q_OS_MACX
	// make it available to options dialog.
	QString resourcesDir;
#endif
	Ui::TextRoomMain ui;


private slots:

	void open();
	bool save();
	bool saveAs();
	void autoSave();
	void options();
	void newFile();
	void help();
	void about();
	void print();
	void insertDate();
	void insertTime();
	void find();
	void find_next();
	void find_previous();
	void sCursor();
	void toggleFullScreen();
	void toggleEscape();
	void documentWasModified();	
	void getFileStatus();
	void readSettings();
	void alarmTime();
	void loadStyleSheet(const QString &fcolor, const QString &bcolor, const QString &scolor);
	void textBold();
	void textItalic();
        void alignRight();
        void alignLeft();
        void alignJustify();
        void alignCenter();
	void textSizeUp();
	void textSizeDown();
	void changeFont();
	void vPositionChanged();
	void hSliderPositionChanged();
	void showScratchPad();
        void spellCheck();
        void insertImage();
	void showMiniFlo();
	void showGetAWord();
	void showMusicRoom();
	void exportToGoogle();

private:
	bool maybeSave();
	QString strippedName(const QString &fullFileName);
	void clearFormating(const QTextBlock& block);	
	void writeSettings();
	void playSound(Mix_Chunk *sound);
	bool saveFile(const QString &fileName);
	void loadFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
	void indentLines(int value);
	int getWordCount(const QString &text);

	HelpDialog *helpDialog;
	OptionsDialog *optionsDialog;
	SearchDialog *searchDialog;
	SelectFont *selectFont;
	AboutDialog *aboutDialog;
	ScratchDialog * scratchDialog;
	GoogleDocsDialog * googleDocsDialog;
	Hunspell * pMS;
	MiniFlo * miniFlo;
	GetAWord * getAWord;
	MusicRoom * musicRoom;
	QSettings *settings;
	QString curFile;
	QString curDir;
	QString lastSearch;
	QString deadlinetext;
	QDate deadline;
	QDate today;
	QString dateFormat;
	bool timeFormatBool;
	QString timeFormat;
	QString defaultDir;
	QString shownName;
	bool wordCountChanged;
	int words;
	int wordcount;
	int parasold;
	int parasnew;
	QFont defaultFont;
	QPixmap bg;
	int alarm;
	int timeOut;
	int sentenceTally;
	QFileSystemWatcher* fw;
	bool optOpenLastFile;
	bool isSaveCursor;
	bool isBackgroundImage;
	bool isPlainText;
	bool isHighlighted;
	int bgIndex;
	int editorWidth;
	int editorTopSpace;
	int editorBottomSpace;
	int numChanges;
	int prevLength;
	int cPosition;
	int textSize;
	int pageCount;
	int characterCount;
        int paragraphSpacing;
        int tabStopWidth;
	int cursorWidth;
        QString language;
	int indentValue;
	QString backgroundImage;
	int pageCountFormula;
	bool ind;
	bool isAutoSave;
	bool isFlowMode;
	bool isSound;
	bool isIndent;
	bool isScrollBarVisible;
	bool isPageCount;
	bool isCharacterCount;
	int channel;
	Mix_Chunk *soundenter;
	Mix_Chunk *soundany;

public:
	QString resourcesDir;

protected:
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);	
};
 
 
#endif
