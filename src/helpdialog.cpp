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
#include "helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) : QDialog(parent)
{
	textEdit = new QTextEdit;
	textEdit->setLineWrapMode(QTextEdit::NoWrap);
	textEdit->setReadOnly(true);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->addWidget(textEdit, 1, 0, 1, 2);
	mainLayout->addWidget(buttonBox, 2, 0, 1, 2);
	setLayout(mainLayout);

	setWindowTitle(tr("TextRoom Help") );
	resize(500, 400);
	
	QString helpText = tr("Keyboard shortcuts:\n\n"
					"F1 - This help screen\n"
					"F11 - Fullscreen on/off\n"
					"Escape - Quit or exit fullscreen (depends on current active window state)\n"
					"Ctrl+H - About\n"
					"Ctrl+M - Minimize TextRoom\n"
					"Ctrl+Q - Quit\n"
					"\n"
					"Ctrl+N - New\n"
					"Ctrl+O - Open\n"
					"Ctrl+S - Save\n"
					"Ctrl+Shift+S - Save as\n"
					"\n"
					"Ctrl+X - Cut\n"
					"Ctrl+C - Copy\n"
					"Ctrl+V - Paste\n"
					"Ctrl+A - Select All\n"
					"Ctrl+Z - Undo (Ctrl+Shift+Z to Redo)\n"
					"Ctrl+T - Indent first lines (useful due to unresolved bug)\n"
					"Ctrl+F - Find\n"
					"F3 - Find next\n"
					"Shift+F3 - Find previous\n"
					"\n"
					"Ctrl+D - Show date and time in statusbar\n"
					"Ctrl+L - Show statistics in statusbar\n"
					"Ctrl+U - Options");
	
	textEdit->setPlainText( helpText );

}
