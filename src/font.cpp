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

#include "font.h"

SelectFont::SelectFont(QWidget *parent) : QDialog(parent)

{
	ui.setupUi(this);
	readSettings();
}

void SelectFont::readSettings()
{
#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif

	QFont font;
	QString currentFormat = settings.value("FontFamily", ui.fontComboBox->currentFont() ).toString();
	font.fromString(currentFormat);
	ui.fontComboBox->setCurrentFont( font );
	ui.boldCheckBox->setChecked( font.bold() );
	ui.italicCheckBox->setChecked( font.italic() );
	ui.sizeSpinBox->setValue( font.pointSize() );
	
	QPalette palette;
	QString color = settings.value("FontColor", "#000000").toString();
	fcolor.setNamedColor( color );
	palette.setColor(ui.fontColorPushButton->backgroundRole(),
		fcolor);
	ui.fontColorPushButton->setPalette(palette);
}

void SelectFont::writeSettings()
{
	#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif

	settings.setValue("FontColor", fcolor.name() );
	
	QFont font;
	font = ui.fontComboBox->currentFont();
	font.setBold(ui.boldCheckBox->isChecked() );
	font.setItalic(ui.italicCheckBox->isChecked() );
	font.setPointSize(ui.sizeSpinBox->value() );
	
	settings.setValue("FontFamily", font.toString() );
}

void SelectFont::on_okPushButton_clicked()
{
	writeSettings();
	accept();
}

void SelectFont::on_fontColorPushButton_clicked()
{
	showColorDialog();
}

void SelectFont::showColorDialog()
{
	QColor c = QColorDialog::getColor(fcolor, this);
	if (c.isValid())
	{
		QPalette palette;
		palette.setColor(ui.fontColorPushButton->backgroundRole(), fcolor = c);
		ui.fontColorPushButton->setPalette(palette);
		ui.fontColorPushButton->setAutoFillBackground(true);
	}
}


void SelectFont::showEvent( QShowEvent * )
{
	readSettings();
}
