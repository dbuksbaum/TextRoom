/****************************************************************************
** Copyright (C) 2008 Omer Bahri Gordebak <gordebak at gmail.com>
**
** website: http://code.google.com/p/getaword/
** All rights reserved.
**
** This file may be used under the terms of the GNU General Public
** License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of
** this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
****************************************************************************/
#ifndef GETAWORD_H
#define GETAWORD_H

#include <QtGui>

#include "ui_getaword.h"

class GetAWord: public QDialog, private Ui::GetAWord
{
	Q_OBJECT

public:
        GetAWord(QWidget *parent = 0);

private slots:
	void newWord();
        void readFile(const QString &fileName);

private:
	QString dictionary;
	QString allWords;
	QStringList wordList;
	QString currentWord;
};

#endif
