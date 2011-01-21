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


#include "urldialog.h"
#include <QtGui>
#include <QWidget>
#include "textroom.h"

UrlDialog::UrlDialog(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	oldUrl();
        connect(ui.okButton, SIGNAL(clicked()), this, SLOT(getUrl()));
        connect(ui.cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

void UrlDialog::getUrl()
{
#ifdef Q_OS_WIN32
	QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName());
#else
	QSettings settings;
#endif
	settings.setValue("Url", ui.urlLineEdit->text());
	accept();
}

void UrlDialog::oldUrl()
{
#ifdef Q_OS_WIN32
	QSettings settings(QSettings::IniFormat, QSettings::UserScope, QApplication::organizationName());
#else
	QSettings settings;
#endif
	ui.urlLineEdit->setText(settings.value("Url", "").toString());
}
