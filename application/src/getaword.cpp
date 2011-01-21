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
#include <QtGui>
#include "getaword.h"
#include "textroom.h"

GetAWord::GetAWord(QWidget *parent)
    : QDialog(parent)
{
        setupUi(this);
        dictionary = "/usr/share/textroom/words.txt";
	readFile(dictionary);
        newWord();

	connect(getButton, SIGNAL(clicked()), this, SLOT(newWord()));
}

void GetAWord::newWord()
{
	int wordCount = wordList.count();
        int getRand = (rand() % wordCount);
	currentWordLabel->setText(wordList[getRand]); 
}

void GetAWord::readFile(const QString &fileName)
{
     QFile file(fileName);
     if (!file.open(QFile::ReadOnly | QFile::Text)) {
         QMessageBox::warning(this, tr("Application"),
                              tr("Cannot read file %1:\n%2.")
                              .arg(fileName)
                              .arg(file.errorString()));
         return;
     }
     QTextStream in(&file);
     allWords = in.readAll();
     wordList = allWords.split("\n");
}
