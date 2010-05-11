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

#include "optionsdialog.h"
#include "textroom.h"

OptionsDialog::OptionsDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	reaSettings();
        QPlastiqueStyle * style = new QPlastiqueStyle();
        OptionsDialog::setStyle(style);

	connect(ui.pushButton, SIGNAL( clicked() ), this, SLOT( startAlarm() ) );
	connect(ui.browseButton, SIGNAL( clicked() ), this, SLOT( selectDir() ) );
}

void OptionsDialog::startAlarm()
{
	if (ui.spinBox->value() > 0)
	{
	setAlarm = ui.spinBox->value();
	writSettings();
	close();	
	}
	else
	{
	setAlarm = 0;
	writSettings();
	}
}

void OptionsDialog::selectDir()
{
	dirSelected = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath());
	ui.defaultSaveLocationLineEdit->setText( dirSelected );
}

void OptionsDialog::reaSettings()
{
#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif

	QDateTime today = QDateTime::currentDateTime();
	QString todaytext = today.toString("yyyyMMdd");
	QStringList fontS;
	QFont font;
	QFont defaultFont;

                 font.fromString( settings.value("StatusFont").toString() );
                 defaultFont.fromString( settings.value("DefaultFont").toString() );

        ui.statusbarFontComboBox->setCurrentFont(font);
        ui.fontComboBox->setCurrentFont(defaultFont);
	
	ui.loadOnStartCheckBox->setChecked( settings.value( "RecentFiles/OpenLastFile", true ).toBool() );
	ui.saveCursorCheckBox->setChecked( settings.value( "RecentFiles/SavePosition", true ).toBool() );
	if ( !ui.loadOnStartCheckBox->isChecked() )
		ui.saveCursorCheckBox->setEnabled( false );
	
	ui.editorWidthSpinBox->setMaximum( settings.value("MaxEditorWidth", 1024).toInt());
	ui.editorTopSpaceSpinBox->setMaximum(settings.value("MaxEditorTopSpace", 768).toInt());
	ui.editorBottomSpaceSpinBox->setMaximum(settings.value("MaxEditorBottomSpace", 1000).toInt());
	ui.wordCountSpinBox->setValue( settings.value("WordCount", 0).toInt());
	ui.pageCountSpinBox->setValue( settings.value("PageCountFormula", 250).toInt());
	ui.fullScreenCheckBox->setChecked( settings.value("WindowState/ShowFullScreen", true).toBool() );
	ui.splashScreenCheckBox->setChecked( settings.value("WindowState/ShowSplashScreen", true).toBool() );
	ui.autoSaveCheckBox->setChecked( settings.value("AutoSave", false).toBool() );
	ui.flowModeCheckBox->setChecked( settings.value("FlowMode", false).toBool() );
	ui.scrollBarCheckBox->setChecked( settings.value("ScrollBar", true).toBool() );
	ui.pageCountCheckBox->setChecked( settings.value("PageCount", false).toBool() );
	ui.soundCheckBox->setChecked( settings.value("Sound", true).toBool() );
	ui.characterCountCheckBox->setChecked( settings.value("CharacterCount", false).toBool() );
        QString datetext = settings.value("Deadline", todaytext).toString();
        date = QDate::fromString(datetext, "yyyyMMdd");
        ui.calendarWidget->setSelectedDate(date);
	ui.editorWidthSpinBox->setValue( settings.value	("EditorWidth", 800).toInt());  
	ui.editorTopSpaceSpinBox->setValue( settings.value("EditorTopSpace", 0).toInt());
	ui.editorBottomSpaceSpinBox->setValue( settings.value("EditorBottomSpace", 0).toInt());
	ui.spinBox->setValue( settings.value("TimedWriting", 0 ).toInt());
        ui.dateComboBox->setCurrentIndex( settings.value("DateFormatInt", 0 ).toInt() );
	ui.defaultSaveLocationLineEdit->setText( settings.value("DefaultDirectory", "").toString() );
        ui.twentyfourCheckBox->setChecked( settings.value("24-Hour" , true).toBool() );
        ui.backgroundLineEdit->setText( settings.value("BackgroundImage", "").toString() );
        ui.statusbarBoldCheckBox->setChecked( settings.value("BoldStatus", false).toBool() );
        ui.statusbarItalicCheckBox->setChecked( settings.value("ItalicStatus", false).toBool() );
        ui.statusbarSpinBox->setValue( settings.value("SizeStatus", 12).toInt() );
        ui.fontSizeSpinBox->setValue( settings.value("DefaultFontSize", 12).toInt() );
        ui.plaintextCheckBox->setChecked( settings.value("PlainText", false).toBool() );
        ui.languageComboBox->setCurrentIndex( settings.value("Language", 0).toInt() );
	ui.indentSpinBox->setValue( settings.value("Indent", 50).toInt() );

	QPalette palette;
	
        fcolor.setNamedColor( settings.value("Colors/FontColor", "#808080" ).toString() );
        palette.setColor(ui.pbFontColor->backgroundRole(), fcolor );
	ui.pbFontColor->setPalette(palette);	

        scolor.setNamedColor( settings.value("Colors/StatusColor", "#202020" ).toString() );
        palette.setColor(ui.pbStatusBarColor->backgroundRole(), scolor );
	ui.pbStatusBarColor->setPalette(palette);

	
        bgcolor.setNamedColor( settings.value("Colors/Background", "#000000" ).toString() );
        palette.setColor(ui.pbEditorBackColor->backgroundRole(), bgcolor );
	ui.pbEditorBackColor->setPalette(palette);
	
}

void OptionsDialog::writSettings()
{

#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif

        settings.setValue("Colors/FontColor", fcolor.name() );
        settings.setValue("Colors/Background", bgcolor.name() );
        settings.setValue("Colors/StatusColor", scolor.name() );

	settings.setValue("RecentFiles/OpenLastFile", ui.loadOnStartCheckBox->isChecked() );
	settings.setValue("RecentFiles/SavePosition", ui.saveCursorCheckBox->isChecked() );
	settings.setValue("ScrollBar", ui.scrollBarCheckBox->isChecked() );

	settings.setValue("WindowState/ShowFullScreen", ui.fullScreenCheckBox->isChecked() );
	settings.setValue("WindowState/ShowSplashScreen", ui.splashScreenCheckBox->isChecked() );
	settings.setValue("Sound", ui.soundCheckBox->isChecked() );
	settings.setValue("AutoSave", ui.autoSaveCheckBox->isChecked() );
	settings.setValue("FlowMode", ui.flowModeCheckBox->isChecked() );
	settings.setValue("PageCount", ui.pageCountCheckBox->isChecked() );
	settings.setValue("CharacterCount", ui.characterCountCheckBox->isChecked() );
	settings.setValue("WordCount", ui.wordCountSpinBox->value() );
	settings.setValue("Deadline", ui.calendarWidget->selectedDate().toString("yyyyMMdd"));
	settings.setValue("EditorWidth", ui.editorWidthSpinBox->value() );
	settings.setValue("TimedWriting", setAlarm );
	settings.setValue("EditorTopSpace", ui.editorTopSpaceSpinBox->value() );
	settings.setValue("EditorBottomSpace", ui.editorBottomSpaceSpinBox->value() );
	settings.setValue("PageCountFormula", ui.pageCountSpinBox->value() );
        settings.setValue("DateFormatInt", ui.dateComboBox->currentIndex() );
        settings.setValue("DateFormat", ui.dateComboBox->currentText() );
	settings.setValue("DefaultDirectory", ui.defaultSaveLocationLineEdit->text() );
        settings.setValue("24-Hour", ui.twentyfourCheckBox->isChecked() );
        settings.setValue("BackgroundImage", ui.backgroundLineEdit->text() );
        settings.setValue("BoldStatus", ui.statusbarBoldCheckBox->isChecked() );
        settings.setValue("ItalicStatus", ui.statusbarItalicCheckBox->isChecked() );
        settings.setValue("SizeStatus", ui.statusbarSpinBox->value() );
        settings.setValue("DefaultFontSize", ui.fontSizeSpinBox->value() );
        settings.setValue("PlainText", ui.plaintextCheckBox->isChecked() );
        settings.setValue("Language", ui.languageComboBox->currentIndex() );
	settings.setValue("Indent", ui.indentSpinBox->value() );
	
	QFont font;
	QFont defaultFont;
	
	font = ui.statusbarFontComboBox->currentFont();
        font.setBold( ui.statusbarBoldCheckBox->isChecked() );
        font.setItalic( ui.statusbarItalicCheckBox->isChecked() );
	font.setPointSize(ui.statusbarSpinBox->value() );
        settings.setValue("StatusFont", font.toString() );

	defaultFont = ui.fontComboBox->currentFont();
	defaultFont.setPointSize(ui.fontSizeSpinBox->value() );
        settings.setValue("DefaultFont", defaultFont.toString() );
   	
}

void OptionsDialog::on_pushButtonOk_clicked()
{
	writSettings();
	accept();
}

void OptionsDialog::showEvent( QShowEvent * )
{
	reaSettings();
}

// BACKGROUND

void OptionsDialog::on_pbEditorBackColor_clicked()
{
	showBackgroundDialog();
}

void OptionsDialog::showBackgroundDialog()
{
	QColor c = QColorDialog::getColor(bgcolor, this);
	if (c.isValid())
	{
		QPalette palette;
		palette.setColor(ui.pbEditorBackColor->backgroundRole(), bgcolor = c);
		ui.pbEditorBackColor->setPalette(palette);
		ui.pbEditorBackColor->setAutoFillBackground(true);
	}
}

// STATUSBARTEXTCOLOR

void OptionsDialog::on_pbStatusBarColor_clicked()
{
	showStatusColorDialog();
}

void OptionsDialog::showStatusColorDialog()
{
	QColor c = QColorDialog::getColor(scolor, this);
	if (c.isValid())
	{
		QPalette palette;
		palette.setColor(ui.pbStatusBarColor->backgroundRole(), scolor = c);
		ui.pbStatusBarColor->setPalette(palette);
		ui.pbStatusBarColor->setAutoFillBackground(false);
	}
}

// TEXTCOLOR

void OptionsDialog::on_pbFontColor_clicked()
{
	showFontColorDialog();
}

void OptionsDialog::showFontColorDialog()
{
	QColor c = QColorDialog::getColor(fcolor, this);
	if (c.isValid())
	{
		QPalette palette;
		palette.setColor(ui.pbFontColor->backgroundRole(), fcolor = c);
		ui.pbFontColor->setPalette(palette);
		ui.pbFontColor->setAutoFillBackground(false);
	}
}

void OptionsDialog::on_backgroundImagePushButton_clicked()
{
                QString fileName = QFileDialog::getOpenFileName(this, tr("Select Image"), QDir::homePath());
                if (!fileName.isEmpty())
                {
                        ui.backgroundLineEdit->setText(fileName);
                }
}

void OptionsDialog::on_restorePushButton_clicked()
{
#ifdef Q_OS_WIN32
        QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

        QSettings settings;
#endif
        settings.clear();
        reaSettings();
    }
