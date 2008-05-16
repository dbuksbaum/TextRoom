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

#include <QtGui> 
#include "textroom.h"
#include "optionsdialog.h"
#include "helpdialog.h"
#include "searchdialog.h"
 
TextRoom::TextRoom(QWidget *parent, Qt::WFlags f)
		: QWidget(parent, f), sentenceTally(0)
{
	setupUi(this);
	setObjectName("textroom");
	//setProperty("class", "mainwindow QLabel");

	readSettings();

	optionsDialog = new OptionsDialog(this);
	helpDialog = new HelpDialog(this);

	new QShortcut ( QKeySequence(QKeySequence::New), this, SLOT( newFile() ) );
	new QShortcut ( QKeySequence(QKeySequence::Open), this, SLOT( open() ) );
	new QShortcut ( QKeySequence(QKeySequence::Save), this, SLOT( save() ) );
	new QShortcut ( QKeySequence(QKeySequence::HelpContents), this, SLOT( help() ) );
	new QShortcut ( QKeySequence(QKeySequence::Underline), this, SLOT( options() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+Shift+S", "Save As")), this, SLOT( saveAs() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+D", "Get Date/Time")), this, SLOT( dateTimeStatsLabel() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+L", "Get Statistics")), this, SLOT( cramStatsLabel() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+T", "Indent First Lines")), this, SLOT( indentFirstLines() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+H", "About TextRoom")), this, SLOT( about() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+Q", "Quit Application")) , this, SLOT( close() ) );
	new QShortcut ( QKeySequence(tr("Alt+F4", "Quit Application")) , this, SLOT( close() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+F", "Find Text")) , this, SLOT( find() ) );
	new QShortcut ( QKeySequence(tr("F11", "Toggle Fullscreen")) , this, SLOT( togleFullScreen() ) );
	new QShortcut ( QKeySequence(tr("Esc", "Toggle Fullscreen")) , this, SLOT( togleEscape() ) );
	new QShortcut ( QKeySequence(tr("Ctrl+M", "Minimize TextRoom")) , this, SLOT( showMinimized() ) );
	new QShortcut ( QKeySequence(tr("F3", "Find Next")) , this, SLOT( find_next() ) );
	new QShortcut ( QKeySequence(tr("Shift+F3", "Find Previous")) , this, SLOT( find_previous() ) );
	
	// Service: show cursor
	new QShortcut ( QKeySequence(tr("Shift+F4", "Show Cursor")) , this, SLOT( sCursor() ) );
	
	#ifdef Q_OS_WIN32

		QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
	#else

		QSettings settings;
	#endif

	settings.setValue("README","Please read the help file"
					  " by pressing F1, the help key, for"
					  " instructions on how to modify this file.");
	fw = new QFileSystemWatcher(this);
	fw->addPath( settings.fileName() );

	connect(fw, SIGNAL(fileChanged(const QString)),
			this, SLOT(readSettings()));
	
	connect(textEdit->document(), SIGNAL(contentsChanged()),
			this, SLOT(documentWasModified()));

//	connect(textEdit, SIGNAL(cursorPositionChanged()), this, SLOT(vPositionChanged()));

	connect(textEdit->verticalScrollBar(), SIGNAL(valueChanged(int)),
			this, SLOT(vPositionChanged()));

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
	
	// auto save counter
	numChanges = 0;
	prevLength = 0;
	
}

void TextRoom::togleEscape()
{
	if ( isFullScreen() )
		togleFullScreen();
	else
		close();

}

void TextRoom::togleFullScreen()
{

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

		writeSettings();
		event->accept();
	}
	else
	{
		event->ignore();
	}
}
 
void TextRoom::about() 
{
	QMessageBox::about(this,"About TextRoom",
				"TextRoom Editor ver. 0.2.4 beta\n\n"
		"Project home page: http://code.google.com/p/textroom/\n\n"
		"Code, help and insights (in alphabetical order) by:\n"
		"Adamvert (from ubuntuforums.org),\n"
		"Magnus Edvardsson (a.k.a. zebulon M),\n"
		"Peter Toushkov\n\n"
		"TextRoom is partially based on\n"
		"The Phrasis project by Jacob R. Rideout:\n"
		"http://code.google.com/p/phrasis/");
}

void TextRoom::newFile()
{
	if (maybeSave())
	{

		textEdit->document()->blockSignals(true);
		textEdit->clear();
		textEdit->document()->blockSignals(false);
		
		setCurrentFile("");
		textEdit->setUndoRedoEnabled(false);
		indentFirstLines();
		textEdit->setUndoRedoEnabled(true);
		textEdit->document()->setModified(false);
		setStatsLabelText(0,0,0);
		horizontalSlider->setVisible(false);
		textEdit->verticalScrollBar()->setValue(0);

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
	if (curFile.isEmpty() || !QFileInfo(curFile).isWritable() )
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
	QString fileName = QFileDialog::getSaveFileName(this);
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void TextRoom::loadFile(const QString &fileName)
{
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
	QString str = codec->toUnicode(data);
	str = QString::fromLocal8Bit(data);
	
	QApplication::setOverrideCursor(Qt::WaitCursor);

	file.seek(0);
	textEdit->document()->blockSignals(true);
	textEdit->setPlainText("");
	textEdit->setUndoRedoEnabled(false);
	indentFirstLines();
	textEdit->append(str);
	textEdit->moveCursor(QTextCursor::Start);
	textEdit->setUndoRedoEnabled(true);
	textEdit->document()->blockSignals(false);

	QApplication::restoreOverrideCursor();

	setCurrentFile(fileName);
	setStatsLabelText(0,0,0);

	vPositionChanged();
}

bool TextRoom::maybeSave()
{
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

	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << textEdit->toPlainText();
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

	QString shownName;
	QString labelToolTip;
	if (curFile.isEmpty())
	{
		shownName = "untitled.txt";
		labelToolTip = "";
   	}
	else
	{
		shownName = strippedName(curFile);
		labelToolTip = fileName;
		curDir = f.absolutePath();
   	}
	setWindowTitle(tr("%1[*] - %2").arg(shownName).arg( qApp->applicationName() ));
	label->setText(shownName);
	label->setToolTip(labelToolTip);
}

QString TextRoom::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}

void TextRoom::indentFirstLines()
{
	// does the user want this, or not?
	QTextBlockFormat modifier;
	modifier.setTextIndent(50);
	modifier.setBottomMargin(10);
	QTextCursor cursor(textEdit->document());
	do {
		cursor.mergeBlockFormat(modifier);
	} while (cursor.movePosition(QTextCursor::NextBlock));
}

void TextRoom::setStatsLabelText(int position, int charsRemoved, int charsAdded)
{
	Q_UNUSED(charsRemoved);
	Q_UNUSED(charsAdded);

	setWindowModified(textEdit->document()->isModified());

	const QString text( textEdit->document()->toPlainText() );

	//Compute words
	QRegExp wordsRX("\\s+");
	QStringList list = text.split(wordsRX,QString::SkipEmptyParts);
	const int words = list.count();

	//Compute paras
	list = text.split("\n",QString::SkipEmptyParts);
	const int paras = list.count();

	//Compute sentences
	QTextBlock block = textEdit->document()->findBlock ( position );

	// 1. characters, 2. words, 3. paragraphs
	
	statsLabel->setText(tr(""
						   "%1 / "
						   ""
						   "%2 / "
						   ""
						   "%3 / "
						   ""
						   "%4 ",
						   "Statistics"
						  ).arg( text.size() ).arg( words ).arg( paras ).arg( (float)text.size()/1800 )
					   );
	statsLabel->setToolTip(tr("characters / words / paragraphs / pages"));

//	QTimer::singleShot( 3500, this, SLOT( getFileStatus() ) );
}

void TextRoom::cramStatsLabel()
{
	statsLabel->setText("Calculating...");
	setStatsLabelText(0,0,0);
}

void TextRoom::dateTimeStatsLabel()
{
	QDateTime now = QDateTime::currentDateTime();
	QString text = now.toString("ddd, d MMM yyyy, hh:mm");
	statsLabel->setText( text );
	statsLabel->setToolTip(tr("Current date and time"));
	QTimer::singleShot( 3500, this, SLOT( getFileStatus() ) );

}

void TextRoom::getFileStatus()
{
	QString statsLabelStr;
	QString statsLabelToolTip;
	if (!textEdit->document()->isModified())
	{
		statsLabelStr = tr("OK");
		statsLabelToolTip = tr("Your file is saved.");
	}
	else	
	{
		statsLabelStr = tr("CHANGED");
		statsLabelToolTip = tr("Your file is not saved!");
	}
	statsLabel->setText( statsLabelStr );
	statsLabel->setToolTip( statsLabelToolTip );
}

void TextRoom::documentWasModified()
{
	setWindowModified(textEdit->document()->isModified());

	if (isAutoSave && numChanges++ > 3) {
		numChanges = 0;	
		save();
	} 

	if ( isFlowMode && textEdit->document()->toPlainText().size() < prevLength ) {
		textEdit->undo();
	} 


	prevLength=textEdit->document()->toPlainText().size();

	vPositionChanged();

	getFileStatus();
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

	QString color = settings.value("Colors/Foreground", "#d0a100" ).toString();
	QString back = settings.value("Colors/Background", "black" ).toString();
	QString status_c = settings.value("Colors/StatusColor", "#404040" ).toString();
	QString scrollb_c = settings.value("Colors/ScrollBarColor", "#1E1E1E" ).toString();

	loadStyleSheet(color, back, status_c, scrollb_c);

	// oxygen does weird stuff with the background
	QApplication::setStyle("plastique");

	QStringList fontS;
	QFont font;
	fontS << settings.value("Font/Font_Settings", textEdit->currentFont() ).toString() 
		<< settings.value("Font/FileName_Settings", label->font() ).toString()
		<< settings.value("Font/Statistics_Settings", statsLabel->font() ).toString();
	
	font.fromString(fontS.at(1));
	if (!(label->font() == font)) 
	{
		label->setFont( font );
		//label->setProperty("class", "mainwindow QLabel");
	}
	
	font.fromString(fontS.at(2));
	if (!(statsLabel->font() == font))
	{
		statsLabel->setFont( font );
		//statsLabel->setProperty("class", "mainwindow QLabel");
	}

	font.fromString(fontS.at(0));
	if (!(textEdit->currentFont() == font)) 
		textEdit->setFont( font );
	
	
	curDir = settings.value("RecentFiles/LastDir", curDir).toString();
	lastSearch = settings.value("TextSearch/LastPhrase", lastSearch).toString();

	isAutoSave = settings.value("AutoSave", false).toBool();
	isFlowMode = settings.value("FlowMode", false).toBool();

	horizontalSlider->setVisible( settings.value("EnableScrollBar", true).toBool() );
	isScrollBarVisible = horizontalSlider->isVisible();
	vPositionChanged();

	if ( optOpenLastFile = settings.value("RecentFiles/OpenLastFile", true).toBool() )
	{
		curFile = settings.value("RecentFiles/LastFile", curFile).toString();
		if ( isSaveCursor = settings.value("RecentFiles/SavePosition", true).toBool() )
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

	settings.setValue("RecentFiles/OpenLastFile", optOpenLastFile);
	if ( optOpenLastFile )
	{
		settings.setValue("RecentFiles/SavePosition", isSaveCursor);
		if ( isSaveCursor )
			settings.setValue("RecentFiles/AtPosition", cPosition);
	}

}

void TextRoom::options()
{
	writeSettings();
	optionsDialog->showNormal();
}

void TextRoom::help()
{
	helpDialog->showNormal();
}

void TextRoom::loadStyleSheet(const QString &fcolor, const QString &bcolor, const QString &scolor, const QString &sbcolor)
{
	QPalette palette;

	palette.setColor(QPalette::Text, fcolor);
	palette.setColor(QPalette::Base, bcolor);
	textEdit->setPalette(palette);
	horizontalSlider->setPalette(palette);

	palette.setColor(QPalette::Window, bcolor);
	TextRoom::setPalette(palette);

	palette.setColor(QPalette::WindowText, scolor);
	label->setPalette(palette);
	statsLabel->setPalette(palette);
	horizontalSlider->setPalette(palette);

	palette.setColor(QPalette::Button, sbcolor);
	horizontalSlider->setPalette(palette);
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

void TextRoom::resizeEvent(QResizeEvent *event)
{
	update();
	sCursor();
	vPositionChanged();
	QWidget::resizeEvent(event);

}
