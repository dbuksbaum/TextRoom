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

#include <QtGui>

#include "newproject.h"

NewProject::NewProject(QWidget *parent) : QDialog(parent)

{
	label = new QLabel(tr("Project Name:"));
	lineEdit = new QLineEdit;
	label->setBuddy(lineEdit);

	addProjectButton = new QPushButton(tr("&Add"));
	addProjectButton->setDefault(true);

	cancelButton = new QPushButton(tr("&Cancel"));
	cancelButton->setDefault(false);

	buttonBox = new QDialogButtonBox(Qt::Horizontal);
	buttonBox->addButton(addProjectButton, QDialogButtonBox::ActionRole);
	buttonBox->addButton(cancelButton, QDialogButtonBox::ActionRole);

	connect(addProjectButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

	QHBoxLayout *topLeftLayout = new QHBoxLayout;
	topLeftLayout->addWidget(label);
	topLeftLayout->addWidget(lineEdit);

	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addLayout(topLeftLayout);
	leftLayout->addStretch(1);

	QGridLayout *mainLayout = new QGridLayout;
	mainLayout->setSizeConstraint(QLayout::SetFixedSize);
	mainLayout->addLayout(leftLayout, 0, 0);
	mainLayout->addWidget(buttonBox, 0, 1);
	setLayout(mainLayout);

	setWindowTitle(tr("Add New Project"));
}

QString NewProject::createNewProject(QWidget *parent)
{
	NewProject *npdlg = new NewProject(parent);
	npdlg->setModal(true);
	QString result;
	if (npdlg->exec() == QDialog::Accepted)
	{
		result = npdlg->lineEdit->text();
	}
	
	return result;
}
