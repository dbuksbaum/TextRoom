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


#include "googledocs.h"
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "gdata/util/string_utils.h"
#include "gdata/client/doc_list_service.h"
#include <QtGui>
#include <QWidget>
#include "textroom.h"

using namespace std;
using gdata::client::DocListService;
using gdata::util::StringUtils;

GoogleDocsDialog::GoogleDocsDialog(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	connect(ui.listPushButton, SIGNAL(clicked()), this, SLOT(listDocs()));
	connect(ui.exportPushButton, SIGNAL(clicked()), this, SLOT(exporttogoogle()));
	connect(ui.closePushButton, SIGNAL(clicked()), this, SLOT(accept()));
}

void GoogleDocsDialog::exporttogoogle()
{
	std::string doc_title = ui.nameLineEdit->text().toStdString();
	std::string email = ui.emailLineEdit->text().toStdString();
	std::string password = ui.passLineEdit->text().toStdString();
	std::string fileName = (QDir::homePath()+"/tmp.googledocs.odt").toStdString();
	DocListService service(email, password, "TextRoom");
        service.UploadDoc(fileName, doc_title);
	listDocs();
}

void GoogleDocsDialog::listDocs()
{
	items.clear();
	ui.listWidget->clear();
	std::string email = ui.emailLineEdit->text().toStdString();
	std::string password = ui.passLineEdit->text().toStdString();
	std::string fileName = (QDir::homePath()+"/tmp.googledocs.odt").toStdString();
	DocListService service(email, password, "TextRoom");
	vector< string > doc_listing;
	string doc_list_feed = DocListService::kDocListScope +
                           DocListService::kDocListFeed;
	doc_listing = service.ListDocuments(doc_list_feed, false);
	for (unsigned int i = 0; i < doc_listing.size(); ++i)
	{
	QString current;
	items << current.fromStdString(doc_listing[i]);
	}
	ui.listWidget->addItems(items);
}
