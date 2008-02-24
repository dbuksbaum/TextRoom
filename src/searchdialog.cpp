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

#include "searchdialog.h"

SearchDialog::SearchDialog(QWidget *parent,
			const QString &lstSearch) : QDialog(parent)

{
	label = new QLabel(tr("Find &what:"));
	lineEdit = new QLineEdit;
	if (!lstSearch.isEmpty()) {
		lineEdit->setText(lstSearch);
		lineEdit->selectAll();
	}
	label->setBuddy(lineEdit);

/*
	caseCheckBox = new QCheckBox(tr("M&atch case"));
	caseCheckBox->setChecked(sCase);

	wholeWordsCheckBox = new QCheckBox(tr("&Whole words"));
	wholeWordsCheckBox->setChecked(sWords);

	backwardCheckBox = new QCheckBox(tr("Search &backward"));
	backwardCheckBox->setChecked(sBckward);
*/

	findButton = new QPushButton(tr("&Find"));
	findButton->setDefault(true);

	cancelButton = new QPushButton(tr("&Cancel"));
	cancelButton->setDefault(false);

	buttonBox = new QDialogButtonBox(Qt::Horizontal);
	buttonBox->addButton(findButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(cancelButton, QDialogButtonBox::ActionRole);

	connect(findButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
//	leftLayout->addWidget(caseCheckBox);
//	leftLayout->addWidget(wholeWordsCheckBox);
//	leftLayout->addWidget(backwardCheckBox);
	leftLayout->addStretch(1);

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addLayout(leftLayout, 0, 0);
	mainLayout->addWidget(buttonBox, 0, 1);
	setLayout(mainLayout);

	setWindowTitle(tr("Find in Text"));
}

QString SearchDialog::useSearchDialog(QWidget *parent,
					const QString &srchString)
{
	SearchDialog *sdlg = new SearchDialog(parent, srchString);
	sdlg->setModal(true);
	QString result;
	if (sdlg->exec() == QDialog::Accepted)
	{
		result = sdlg->lineEdit->text();
	}
	
	return result;
}
