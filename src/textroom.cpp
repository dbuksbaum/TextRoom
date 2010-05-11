/****************************************************************************
** Copyright (C) 2008 Petar Toushkov <peter dot toushkov at gmail.com>
** Copyright (C) 2008 Omer Bahri Gordebak <gordebak at gmail.com>
**
** Additional help, code and insights by:
** adamvert - from http://ubuntuforums.org/
** zebulon M - from http://ubuntuforums.org/
**
** Artwork by Edward Solorukhin <arch1000@gmail.com>
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

#include <QtGui> 
#include "textroom.h"
#include "optionsdialog.h"
#include "helpdialog.h"
#include "searchdialog.h"
#include "font.h"
#include "about.h"
#include "scratchpad.h"
#include "SDL/SDL.h"
// *** IF USING XCODE ON MACOS X, CHANGE THE FOLLOWING LINE TO:  #include "SDL_mixer/SDL_mixer.h"
#include "SDL/SDL_mixer.h"
#include "iostream"

TextRoom::TextRoom(QWidget *parent, Qt::WFlags f)
		: QWidget(parent, f), sentenceTally(0)
{
	setupUi(this);
	setObjectName("textroom");
	
// Read settings saved by Options Dialog.
	readSettings();

// Set the default values for variables.
	numChanges = 0;
	prevLength = 0;
	wordcount = 0;
	alarm = 0;
	parasold = 0;
        isHighlighted = false;

// Create the dialog windows.
	optionsDialog = new OptionsDialog(this);
	helpDialog = new HelpDialog(this);
	selectFont = new SelectFont(this);
        aboutDialog = new AboutDialog(this);
	scratchDialog = new ScratchDialog(this);

// Sound adjustments.
        int audio_rate = 11025;
        Uint16 audio_format = AUDIO_S16SYS;
        int audio_channels = 2;
	int audio_buffers = 1024;
	
	if ( SDL_Init(SDL_INIT_AUDIO) < 0 ) {
	fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
	exit(1);
	}
	atexit(SDL_Quit);
	
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
	printf("Unable to initialize audio: %s\n", Mix_GetError());
	exit(1);
	}

// Load sounds.
        soundenter = Mix_LoadWAV("/usr/share/sounds/keyenter.wav");
	if(soundenter == NULL) {
		printf("Unable to load WAV file: %s\n", Mix_GetError());
	}

        soundany = Mix_LoadWAV("/usr/share/sounds/keyany.wav");
	if(soundany == NULL) {
		printf("Unable to load WAV file: %s\n", Mix_GetError());
	}
		
// Create the keyboard shortcuts.
	new QShortcut ( QKeySequence(QKeySequence::New), this, SLOT( newFile() ) );
	new QShortcut ( QKeySequence(QKeySequence::Open), this, SLOT( open() ) );
	new QShortcut ( QKeySequence(QKeySequence::Save), this, SLOT( save() ) );
	new QShortcut ( QKeySequence(QKeySequence::HelpContents), this, SLOT( help() ) );
        new QShortcut ( QKeySequence(tr("F2", "Options")), this, SLOT( options() ) );
        new QShortcut ( QKeySequence(tr("F3", "About")), this, SLOT( about() ) );
        new QShortcut ( QKeySequence(tr("F5", "Spell Check")), this, SLOT( spellCheck() ) );
        new QShortcut ( QKeySequence(tr("F6", "Scratch Pad")), this, SLOT( showScratchPad() ) );
        new QShortcut ( QKeySequence(tr("Ctrl+P", "Print")), this, SLOT( print() ) );
	new QShortcut ( QKeySequence(tr("Shift+Ctrl+S", "Save As")), this, SLOT( saveAs() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+D", "Insert Date")), this, SLOT( insertDate() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+T", "Insert Time")), this, SLOT( insertTime() ) );	
	new QShortcut ( QKeySequence(tr("Ctrl+Q", "Quit Application")) , this, SLOT( close() ) );
	new QShortcut ( QKeySequence(tr("Alt+F4", "Quit Application")) , this, SLOT( close() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+F", "Find Text")) , this, SLOT( find() ) );
	new QShortcut ( QKeySequence(tr("F11", "Toggle Fullscreen")) , this, SLOT( togleFullScreen() ) );
	new QShortcut ( QKeySequence(tr("Esc", "Toggle Fullscreen")) , this, SLOT( togleEscape() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+M", "Minimize TextRoom")) , this, SLOT( showMinimized() ) );
        new QShortcut ( QKeySequence(tr("F4", "Find Next")) , this, SLOT( find_next() ) );
        new QShortcut ( QKeySequence(tr("Ctrl+F4", "Find Previous")) , this, SLOT( find_previous() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+B", "Bold")) , this, SLOT( textBold() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+I", "Italic")) , this, SLOT( textItalic() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+Up", "Increase Text Size")) , this, SLOT( textSizeUp() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+Down", "Decrease Text Size")) , this, SLOT( textSizeDown() ) );	
	new QShortcut ( QKeySequence(tr("Ctrl+W", "Select Font")) , this, SLOT( changeFont() ) );	
	
	// Service: show cursor
	new QShortcut ( QKeySequence(tr("Shift+F4", "Show Cursor")) , this, SLOT( sCursor() ) );

// Adjust the settings file for Windows.
#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

// Create the settings file.
	QSettings settings;
#endif	


	fw = new QFileSystemWatcher(this);
	fw->addPath( settings.fileName() );

// If file is changed, read the settings.
	connect(fw, SIGNAL(fileChanged(const QString)),
			this, SLOT(readSettings()));
// If the document is changed, do some stuff.
	connect(textEdit->document(), SIGNAL(contentsChanged()),
			this, SLOT(documentWasModified()));

// If position is changed, scroll.
	connect(textEdit->verticalScrollBar(), SIGNAL(valueChanged(int)),
			this, SLOT(vPositionChanged()));
// If horizontal scrollar is changed, scroll.
	connect(horizontalSlider, SIGNAL(valueChanged(int)),
			this, SLOT(hSliderPositionChanged()));

	// check if we need to open some file at startup
	const QStringList args = QCoreApplication::arguments();
	if (args.count() == 2)
	{
		QFile file( args.at(1) );
			if ( file.exists() )
				curFile = args.at(1);
	}
	
	if (!curFile.isEmpty())
		loadFile(curFile);
	else
		newFile();


	// set cursor position
	if ( isSaveCursor )
	{
		QTextCursor c;
		c = textEdit->textCursor();
		c.setPosition(cPosition);
		textEdit->setTextCursor(c);
	}

	writeSettings();

// Refresh the file status every second.
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(getFileStatus()));
	timer->start(1000);
}

void TextRoom::playSound(Mix_Chunk *sound)
{
// Play the sounds if sound is enabled.
	if(isSound)
	{
	channel = Mix_PlayChannel(-1, sound, 0);
	if(channel == -1) {
	printf("Unable to play WAV file: %s\n", Mix_GetError()); }
	}
}

void TextRoom::togleEscape()
{
// Toggle Fullscreen or if visible hide Help when ESC is pressed.
        if ( helpDialog->isVisible() || aboutDialog->isVisible() || scratchDialog->isVisible() )
	{
	helpDialog->hide();
        aboutDialog->hide();
	scratchDialog->hide();
	}
	else if ( isFullScreen() )
		togleFullScreen();
	else
		close();

}

void TextRoom::insertDate()
{
// Insert date.
	QDateTime today = QDateTime::currentDateTime();
	QString date = today.toString(dateFormat);
	setWindowModified(textEdit->document()->isModified());

        textEdit->insertPlainText(date);
}

void TextRoom::insertTime()
{
// Insert time.
	QDateTime now = QDateTime::currentDateTime();
	QString clock = now.toString(timeFormat);
	setWindowModified(textEdit->document()->isModified());

        textEdit->insertPlainText(clock);
}

void TextRoom::togleFullScreen()
{
// Toggle Full Screen.

	if ( !isFullScreen() )
		showFullScreen();
	else
		showNormal();
//	sCursor();
}

void TextRoom::closeEvent(QCloseEvent *event)
{
//	qDebug() << "closing";
	if (maybeSave())
	{
		fw->disconnect();

		// save cursor position
		if ( isSaveCursor )
		{
			QTextCursor c;
			c = textEdit->textCursor();
			cPosition = c.position();
		}
		wordcount = 0;
		alarm = 0;
		writeSettings();
		event->accept();
	}
	else
	{
		event->ignore();
	}
}
 
void TextRoom::newFile()
{
	if (maybeSave())
	{
		textEdit->document()->blockSignals(true);
		textEdit->clear();
		scratchDialog->ui.scratchTextEdit->clear();
		textEdit->document()->blockSignals(false);
		
		setCurrentFile("");
		textEdit->setUndoRedoEnabled(true);
		textEdit->document()->setModified(false);
		textEdit->verticalScrollBar()->setValue(0);
                textEdit->setFont(defaultFont);
		indentLines(indentValue);
	}
}

void TextRoom::open()
{
	if (maybeSave())
	{
		QString dirToOpen;
		if ( curDir.isEmpty() )
		{
			dirToOpen = QDir::homePath();
	   	}
	   	else
	   	{
	   		dirToOpen = curDir;
	  	}
		QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), dirToOpen);
		if (!fileName.isEmpty())
		{
			loadFile(fileName);
	   	}
	}
}

bool TextRoom::save()
{
        if (curFile.isEmpty() || !QFileInfo(curFile).isWritable() || shownName == "Untitled.txr")
	{
		return saveAs();
	}
	else
	{
		return saveFile(curFile);
	}
}

bool TextRoom::saveAs()
{
        QString extension;
        if ( isPlainText )
        {
            extension = "*.txt";
        }
        else
        {
            extension = "*.txr";
        }
        QString fileName = QFileDialog::getSaveFileName(this, "Save As", defaultDir + "/" + extension, "TextRoom Documents (*.txr);;Html Files (*.htm *.html);;Text Documents (*.txt)");
	if (!fileName.isEmpty())
	{
		return saveFile(fileName);
	}
	else
	{
		return true;
	}
}

void TextRoom::autoSave()
{
        if (shownName == "Untitled.txr")
	{
                QString fileName = defaultDir + "/UntitledAutoSaved.txr";
		saveFile(fileName);
	}
	else
	{
		save();
	}
}

void TextRoom::loadFile(const QString &fileName)
{
// Loads the file.
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, qApp->applicationName(),
							 tr("Cannot read file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		newFile();
		return;
	}

        QByteArray data = file.readAll();
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	QString strall = codec->toUnicode(data);
	QStringList strlist = strall.split("\n<split>\n", QString::SkipEmptyParts);
	QString strscratch = strlist.at(0);
	QString strdoc = strlist.at(1);

	QApplication::setOverrideCursor(Qt::WaitCursor);

	file.seek(0);
	textEdit->document()->blockSignals(true);
	textEdit->setPlainText("");
	textEdit->setUndoRedoEnabled(false);
	textEdit->append(strdoc);
	textEdit->moveCursor(QTextCursor::Start);
	textEdit->setUndoRedoEnabled(true);
	textEdit->document()->blockSignals(false);
	scratchDialog->ui.scratchTextEdit->setPlainText("");
	scratchDialog->ui.scratchTextEdit->append(strscratch);

	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	if (fileName.endsWith("txt"))
	{
		textEdit->setFont(defaultFont);
	}
	QString text = textEdit->document()->toPlainText();
	parasold = text.count("\n", Qt::CaseSensitive);
	indentLines(indentValue);
	vPositionChanged();
	getFileStatus();
}

bool TextRoom::maybeSave()
{
	if (textEdit->document()->isEmpty())
	{
	return true;
	}
	if (textEdit->document()->isModified())
	{
		QMessageBox::StandardButton ret;
		ret = QMessageBox::warning(this, qApp->applicationName(),
								   tr("The document has been modified.\n"
									  "Do you want to save your changes?"),
								   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		if (ret == QMessageBox::Save)
			return save();
		else if (ret == QMessageBox::Cancel)
			return false;
	}
	return true;
}

bool TextRoom::saveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, qApp->applicationName(),
							 tr("Cannot write file %1:\n%2.")
							 .arg(fileName)
							 .arg(file.errorString()));
		return false;
	}
	QTextStream out(&file);
	out.setCodec("UTF-8");

// If filename extension is .txt then convert to plain text or Only Plain Text Option is selected.
	QApplication::setOverrideCursor(Qt::WaitCursor);
        if (fileName.endsWith("txt") || isPlainText )
	{
		out << textEdit->document()->toPlainText();
	}
	else if (fileName.endsWith("txr"))
	{
		QByteArray ba = "utf-8";
		
		out <<scratchDialog->ui.scratchTextEdit->document()->toHtml(ba) << "\n<split>\n" << textEdit->document()->toHtml(ba);
	}
	else
	{
		QByteArray ba = "utf-8";
		out << textEdit->document()->toHtml(ba);
	}
	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	documentWasModified();	
	return true;
}

void TextRoom::setCurrentFile(const QString &fileName)
{
	curFile = fileName;

	const QFileInfo f(fileName);
	
	textEdit->document()->setModified(false);
	setWindowModified(false);

	if (curFile.isEmpty())
	{
                shownName = "Untitled.txr";
   	}
	else
	{
		shownName = strippedName(curFile);
		curDir = f.absolutePath();
   	}
	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg( qApp->applicationName() ));
}

QString TextRoom::strippedName(const QString &fullFileName)
{
// Strip the filename from the full file address.
	return QFileInfo(fullFileName).fileName();
}

void TextRoom::getFileStatus()
{
// Calculate deadline
	QString showdeadline;
	QString target;
        int daysremaining;
        QString todaytext = QDate::currentDate().toString("yyyyMMdd");
        today = QDate::fromString(todaytext, "yyyyMMdd");
        daysremaining = today.daysTo(deadline);
	QString daysto;
	daysto.setNum(daysremaining);
        if (daysremaining <= 0)
        {
            showdeadline = "";
        }
        else
        {
            showdeadline = daysto + " Days remaining. ";
        }
	int percent;
	QString percenttext;
	QString statsLabelStr;
	QString statsLabelToolTip;
// Show clock.
	QDateTime now = QDateTime::currentDateTime();
        QString clock = now.toString( timeFormat );

        const QString text( textEdit->document()->toPlainText() );

//Compute word count
	QRegExp wordsRX("\\s+");
	QStringList list = text.split(wordsRX,QString::SkipEmptyParts);
	QStringList listSelected = textEdit->textCursor().selection().toPlainText().split(wordsRX, QString::SkipEmptyParts);
	const int words = list.count();
	const int wordsSelected = listSelected.count();
	if (wordsSelected == 0)
	{
		selectedText = "";
	}
	else
	{
		selectedText = selectedText.setNum(wordsSelected);
		selectedText = selectedText + "/";
	}
	if (isPageCount)
	{
		float pageC = ((words/pageCountFormula)+1);
		pageCount = (int)pageC;
		pageCountText = pageCountText.setNum(pageCount);
                pageText = " Pages:" + pageCountText;
	}
	else
	{
		pageText = "";
	}
// Compute Character Count
	if (isCharacterCount)
	{
             QStringList charsWithoutLineEnds = text.split("\n", QString::SkipEmptyParts);
	     QString charsCombined = charsWithoutLineEnds.join("");
             QStringList charsWithoutReturns = charsCombined.split("\r", QString::SkipEmptyParts);
	     charsCombined = charsWithoutReturns.join("");
             QStringList charsWithoutTabs = charsCombined.split("\t", QString::SkipEmptyParts);
	     charsCombined = charsWithoutTabs.join("");
		characterCount = charsCombined.size();
		characterCountText = characterCountText.setNum(characterCount);
                characterText = " Characters:" + characterCountText;
	}
	else
	{
		characterText = "";
	}
	if (wordcount == 0)
	{
                        target = characterText + pageText;
	}
	else if (words < wordcount || words > wordcount)
	{
		float f = words*100/wordcount;
		percent = (int)f;
		percenttext = percenttext.setNum(percent);
                target = " Target:" + wordcounttext + "(%" + percenttext + ")" + characterText + pageText;
	}
        deadlineLabel->setText(showdeadline + clock);
        statsLabel->setText("Words:" + selectedText + tr("%1").arg(words) + target);
}

void TextRoom::documentWasModified()
{
// If document is modified, do stuff.
	setWindowModified(textEdit->document()->isModified());
	
	QString text = textEdit->document()->toPlainText();
	parasnew = text.count("\n", Qt::CaseSensitive);

	if (isAutoSave && numChanges++ > 200) {
		numChanges = 0;	
		autoSave();
	} 

	if ( isFlowMode && textEdit->document()->toPlainText().size() < prevLength ) {
		textEdit->undo();
	} 

	prevLength=textEdit->document()->toPlainText().size();

// If a new paragraph created, play keyenter, else play keyany.
	if (parasnew > parasold)
	{ playSound(soundenter); }
	else
	{ playSound(soundany);}

	parasold = parasnew;

	vPositionChanged();

}

void TextRoom::alarmTime()
{
// Show a message if time is out.
	alarm = 0;
	QMessageBox::warning(this, qApp->applicationName(), tr("Time is out.\n"), QMessageBox::Ok);
	writeSettings();
	readSettings();
}

void TextRoom::readSettings()
{
#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif

	QFile file( settings.fileName() );
	if ( !file.exists() )
	{
		togleFullScreen();
		writeSettings();
		return;
	}

	if ( settings.value("WindowState/ShowFullScreen", true).toBool() )
	{
		if ( !isFullScreen() )
			showFullScreen();
   	}
	else
	{
		showNormal();
		QPoint pos = settings.value("WindowState/TopLeftPosition", QPoint(100, 100)).toPoint();
		QSize size = settings.value("WindowState/WindowSize", QSize(300, 200)).toSize();
		resize(size);
		move(pos);
	}

        QString foregroundColor = settings.value("Colors/FontColor", "#808080" ).toString();
        QString back = settings.value("Colors/Background", "#000000" ).toString();
        QString status_c = settings.value("Colors/StatusColor", "#202020" ).toString();

        loadStyleSheet(foregroundColor, back, status_c);

	// oxygen does weird stuff with the background
	QApplication::setStyle("plastique");

        QFont font;
        font.fromString( settings.value("StatusFont").toString());
        defaultFont.fromString( settings.value("DefaultFont").toString() );

        statsLabel->setFont( font );
        deadlineLabel->setFont ( font ) ;

	curDir = settings.value("RecentFiles/LastDir", curDir).toString();
	lastSearch = settings.value("TextSearch/LastPhrase", lastSearch).toString();

	QDateTime today = QDateTime::currentDateTime();
	QString todaytext = today.toString("yyyyMMdd");
	
// Read all the settings.
	isAutoSave = settings.value("AutoSave", false).toBool();
	isFlowMode = settings.value("FlowMode", false).toBool();
	isSound = settings.value("Sound", true).toBool();
	isPageCount = settings.value("PageCount", false).toBool();
	isCharacterCount = settings.value("CharacterCount", false).toBool();
	deadlinetext = settings.value("Deadline", todaytext).toString();
	deadline = QDate::fromString(deadlinetext, "yyyyMMdd");
	wordcount = settings.value("WordCount", 0).toInt();
	wordcounttext = settings.value("WordCount", 0).toString();
	editorWidth = settings.value("EditorWidth", 800).toInt();
	editorTopSpace = settings.value("EditorTopSpace", 0).toInt();
	editorBottomSpace = settings.value("EditorBottomSpace", 0).toInt();
	alarm = settings.value("TimedWriting", 0).toInt();
	pageCountFormula = settings.value("PageCountFormula", 250).toInt();
        dateFormat = settings.value("DateFormat", "d MMMM yyyy dddd").toString();
        timeFormatBool = settings.value("24-Hour", true ).toBool();
	defaultDir = settings.value("DefaultDirectory", QDir::homePath()).toString();
        backgroundImage = settings.value("BackgroundImage", "").toString();
        isPlainText = settings.value("PlainText", false).toBool();
        language = settings.value("Language", 0).toInt();
	indentValue = settings.value("Indent", 50).toInt();

	indentLines(indentValue);

        if ( isPlainText )
        {
            QString text( textEdit->document()->toPlainText() );
            textEdit->document()->clear();
            textEdit->insertPlainText(text);
            textEdit->setAcceptRichText( false );
        }
        else
        {
            textEdit->setAcceptRichText( true );
        }

        if ( timeFormatBool )
        {
            timeFormat = "h:mm";
        }
        else
        {
            timeFormat = "h:mm AP";
        }

	horizontalSlider->setVisible( settings.value("ScrollBar", true).toBool() );
	isScrollBarVisible = horizontalSlider->isVisible();
	vPositionChanged();

	topSpacer->changeSize(20, editorTopSpace, QSizePolicy::Maximum, QSizePolicy::Maximum);
	bottomSpacer->changeSize(20, editorBottomSpace, QSizePolicy::Maximum, QSizePolicy::Maximum);
	
	timeOut = alarm * 60000;
	if (alarm != 0)
	{
		QTimer::singleShot(timeOut, this, SLOT(alarmTime()));
	}
	
	textEdit->setMaximumWidth(editorWidth);


	if ( (optOpenLastFile = settings.value("RecentFiles/OpenLastFile", true).toBool()) )
	{
		curFile = settings.value("RecentFiles/LastFile", curFile).toString();
		if ( (isSaveCursor = settings.value("RecentFiles/SavePosition", true).toBool() ))
			cPosition = settings.value("RecentFiles/AtPosition", cPosition).toInt();
	}
}

void TextRoom::writeSettings()
{

#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif

	if ( !isFullScreen() )
	{
		settings.setValue("WindowState/TopLeftPosition", pos());
		settings.setValue("WindowState/WindowSize", size());
	}

	settings.setValue("WindowState/ShowFullScreen", isFullScreen());
	settings.setValue("RecentFiles/LastFile", curFile);
	settings.setValue("RecentFiles/LastDir", curDir);
	settings.setValue("TextSearch/LastPhrase", lastSearch);
	settings.setValue("TimedWriting", alarm);

	int maxEditorWidth = width();
	int maxEditorTopSpace = (int)((height() - 56)/2) ;
	int maxEditorBottomSpace = (int)((height() - 56)/2);
	settings.setValue("MaxEditorWidth", maxEditorWidth);
	settings.setValue("MaxEditorTopSpace", maxEditorTopSpace);
	settings.setValue("MacEditorBottomSpace", maxEditorBottomSpace);


	settings.setValue("RecentFiles/OpenLastFile", optOpenLastFile);
	if ( optOpenLastFile )
	{
		settings.setValue("RecentFiles/SavePosition", isSaveCursor);
		if ( isSaveCursor )
			settings.setValue("RecentFiles/AtPosition", cPosition);
	}

	settings.setValue("README","Please read the help file"
					  " by pressing F1, the help key, for"
					  " instructions on how to modify this file.");
}

void TextRoom::options()
{
// If options are changed, read settings again.
	writeSettings();
	if (optionsDialog->exec() == QDialog::Accepted)
	{
		readSettings();
	}
}

void TextRoom::help()
{
	if (!helpDialog->isVisible())
	{
	int x = (width()/2)-351;
	int y = (height()/2)-150;
	helpDialog->move(x,y);
	helpDialog->setWindowFlags(Qt::FramelessWindowHint);
	helpDialog->showNormal();
	}
	else
	{
	helpDialog->hide();
	}
}

void TextRoom::loadStyleSheet(const QString &fcolor, const QString &bcolor, const QString &scolor)
{

        QColor textColor;
        textColor.setNamedColor(fcolor);
        QColor backgroundColor;
        backgroundColor.setNamedColor(bcolor);
        QColor statusbarColor;
        statusbarColor.setNamedColor(scolor);
        QPalette palette;
        palette.setColor(QPalette::Text, textColor);
        palette.setColor(QPalette::Base, QColor(0, 0, 0, 0));
	textEdit->setPalette(palette);

        QPalette bgPalette;
        if ( backgroundImage == 0 )
        {
        bgPalette.setColor(QPalette::Window, backgroundColor);
        }
        else
        {
        QPixmap bgmain;
        bgmain.load( backgroundImage );
        QDesktopWidget* desktopWidget = QApplication::desktop();
        QRect rect = desktopWidget->geometry();
        QSize size(rect.width() , rect.height());
        QPixmap bg(bgmain.scaled(size));
        bgPalette.setBrush(QPalette::Window, bg);
        }
        TextRoom::setPalette(bgPalette);

	QPalette palette2;
        palette2.setColor(QPalette::WindowText, statusbarColor);
        palette2.setColor(QPalette::Window, QColor(0, 0, 0, 0));

	horizontalSlider->setPalette(palette2);
	statsLabel->setPalette(palette2);
	deadlineLabel->setPalette(palette2);
	
}

void TextRoom::find()
{
	QString sString = SearchDialog::useSearchDialog(this, lastSearch);
	if (!sString.isEmpty())
	{
		lastSearch = sString;
		textEdit->find( sString );
		writeSettings();
	}
	
}

void TextRoom::find_next()
{
	if (!lastSearch.isEmpty())
	{
		textEdit->find( lastSearch );
	}
}

void TextRoom::find_previous()
{
	if (!lastSearch.isEmpty())
	{
		textEdit->find( lastSearch, QTextDocument::FindBackward );
	}
}

void TextRoom::sCursor()
{
	textEdit->ensureCursorVisible();
}

void TextRoom::resizeEvent(QResizeEvent *event)
{
	update();
	sCursor();
	QWidget::resizeEvent(event);

}

void TextRoom::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    if ( !isPlainText )
    {
	QTextCursor cursor = textEdit->textCursor();
	cursor.mergeCharFormat(format);
	textEdit->mergeCurrentCharFormat(format);
    }
}

void TextRoom::textBold()
{
	QTextCharFormat fmt;
	QTextCursor cursor = textEdit->textCursor();
	if (cursor.charFormat().fontWeight() == 75)
	{
		fmt.setFontWeight(50);
	}
	else
	{
		fmt.setFontWeight(75);
	}
	mergeFormatOnWordOrSelection(fmt);
}

void TextRoom::textItalic()
{
	QTextCharFormat fmt;
	QTextCursor cursor = textEdit->textCursor();
	if (cursor.charFormat().fontItalic())
	{
		fmt.setFontItalic(false);
	}
	else
	{
		fmt.setFontItalic(true);
	}
	mergeFormatOnWordOrSelection(fmt);
}

void TextRoom::textSizeUp()
{
	textSize = textEdit->currentFont().pointSize();
	textSize++;
	QTextCharFormat fmt;
	fmt.setFontPointSize(textSize);
	mergeFormatOnWordOrSelection(fmt);
}

void TextRoom::textSizeDown()
{
	textSize = textEdit->currentFont().pointSize();
	textSize--;
	QTextCharFormat fmt;
	fmt.setFontPointSize(textSize);
	mergeFormatOnWordOrSelection(fmt);
}

void TextRoom::changeFont()
{
	if (selectFont->exec() == QDialog::Accepted)
	{
	
	#ifdef Q_OS_WIN32
		QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
	#else

		QSettings settings;
	#endif

                QString currentFormat = settings.value("FontFamily", textEdit->textCursor().charFormat().fontFamily() ).toString();
		QTextCharFormat fmt;
                QString fontcolor = settings.value("FontColor", "000000").toString();
		QColor color;
		color.setNamedColor(fontcolor);
		QBrush brush(color, Qt::SolidPattern);
		QFont font;
		font.fromString(currentFormat);
		fmt.setFont(font);
		fmt.setForeground(brush);
		
		mergeFormatOnWordOrSelection(fmt);
	}
}

void TextRoom::vPositionChanged()
{
	horizontalSlider->setMinimum(textEdit->verticalScrollBar()->minimum());
	horizontalSlider->setMaximum(textEdit->verticalScrollBar()->maximum());
	if ( isScrollBarVisible )
		horizontalSlider->setVisible(textEdit->verticalScrollBar()->maximum());
	horizontalSlider->setValue( textEdit->verticalScrollBar()->value());
}

void TextRoom::hSliderPositionChanged()
{
	textEdit->verticalScrollBar()->setValue( horizontalSlider->value() );
}

void TextRoom::print()
{
     QTextDocument *document = textEdit->document();
     QPrinter printer;

     QPrintDialog *dlg = new QPrintDialog(&printer, this);
     if (dlg->exec() != QDialog::Accepted)
         return;

     document->print(&printer);
}

void TextRoom::about()
{
        if (!aboutDialog->isVisible())
        {
        int x = (width()/2)-171;
        int y = (height()/2)-171;
        aboutDialog->move(x,y);
        aboutDialog->setWindowFlags(Qt::FramelessWindowHint);
        aboutDialog->showNormal();
        }
        else
        {
        aboutDialog->hide();
        }
}

void TextRoom::spellCheck()
{
	bool silent = true;
	if (isSound)
	{
		isSound = false;
		silent = false;
	}
	else
		silent = true;
              QString textVar = textEdit->document()->toPlainText();
              textVar.replace(" ", "+");
              textVar.replace("\n", "+");
              textVar.replace("\t", "+");
              textVar.replace("\r", "+");
              textVar.replace(".", "+");
              textVar.replace(",", "+");
              textVar.replace(";", "+");
              textVar.replace("!", "+");
              textVar.replace("?", "+");
              textVar.replace("(", "+");
              textVar.replace(")", "+");
              textVar.replace(":", "+");
              textVar.replace("@", "+");
              textVar.replace("&", "+");
              textVar.replace("$", "+");
              textVar.replace("%", "+");
              textVar.replace("\"", "+");
              QStringList wordList = textVar.split("+", QString::SkipEmptyParts);

              char * affFile = (char *) "/usr/share/myspell/dicts/en_US.aff";
              char * dicFile = (char *) "/usr/share/myspell/dicts/en_US.dic";
              if (language == 0)
              {
                    affFile = (char *) "/usr/share/myspell/dicts/en_US.aff";
                    dicFile = (char *) "/usr/share/myspell/dicts/en_US.dic";
              }
              else if (language == 1)
              {
                    affFile = (char *) "/usr/share/myspell/dicts/tr.aff";
                    dicFile = (char *) "/usr/share/myspell/dicts/tr.dic";
              }

              pMS= new Hunspell(affFile, dicFile);
              QTextCharFormat highlightFormat;
              highlightFormat.setUnderlineColor(Qt::red);
              highlightFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
              QTextCharFormat defaultFormat;
              defaultFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
              if ( !isHighlighted )
                 isHighlighted = true;
              else
              {
                  isHighlighted = false;
              }
              QTextCursor findCursor(textEdit->document());
              findCursor.movePosition(QTextCursor::Start);

              foreach (QString word, wordList)
              {
              QTextCursor highlightCursor(textEdit->document()->find(word, findCursor));
              findCursor.setPosition(highlightCursor.position());
              findCursor.movePosition(QTextCursor::EndOfWord);
              QByteArray ba = word.toUtf8();
              char * wordChar = ba.data();
              int correct = pMS->spell(wordChar);
              if ( !correct && isHighlighted )
                    highlightCursor.mergeCharFormat(highlightFormat);
              else
              {
                    QTextCursor notUnderlined(textEdit->document()->find(" ", findCursor));
                    notUnderlined.mergeCharFormat(defaultFormat);
                    highlightCursor.mergeCharFormat(defaultFormat);
                }
              }
	if (silent)
		isSound = false;
	else
		isSound = true;
}

void TextRoom::showScratchPad()
{
        if (!scratchDialog->isVisible())
        {
        int x = (width()/2)-171;
        int y = (height()/2)-171;
	scratchDialog->move(x, y);
        scratchDialog->setWindowFlags(Qt::FramelessWindowHint);
        scratchDialog->showNormal();
        }
        else
        {
        scratchDialog->hide();
        }
}

void TextRoom::indentLines(int value)
{
	bool silent = true;
	if (isSound)
	{
		isSound = false;
		silent = false;
	}
	else
		silent = true;
	QString text = textEdit->document()->toPlainText();
	int paras = text.count("\n", Qt::CaseSensitive)+1;
	QTextCursor tc = textEdit->textCursor();
        tc.movePosition(QTextCursor::Start);
	for (int i=0; i<paras; i++)
	{
	QTextBlockFormat tfor;
	tfor.setTextIndent(value);
	tc.mergeBlockFormat(tfor);
	tc.movePosition(QTextCursor::NextBlock);
	}
	if (silent)
		isSound = false;
	else
		isSound = true;
}
