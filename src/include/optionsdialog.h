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

#ifndef __OPTIONSDIALOG_H__
#define __OPTIONSDIALOG_H__

#include <QDialog>

#include "ui_optionsdialog.h"

class OptionsDialog : public QDialog
{
	Q_OBJECT

public:
	OptionsDialog(QWidget *parent = 0);

private slots:
	void reaSettings();
	void writSettings();
	void on_pushButtonOk_clicked();
	void on_pbFontColor_clicked();
	void on_pbEditorBackColor_clicked();
        void on_pbStatusBarColor_clicked();
        void on_backgroundImagePushButton_clicked();
        void on_restorePushButton_clicked();
	void showFontColorDialog();
	void showBackgroundDialog();
	void showStatusColorDialog();
	void startAlarm();
	void selectDir();

private:
        QColor fcolor;
        QColor bgcolor;
        QColor scolor;
        QColor sbcolor;
	int setAlarm;
	QString dirSelected;
        QDate date;

private:

	Ui::OptionsDialog ui;

protected:
	void showEvent( QShowEvent * );
};

#endif // __OPTIONSDIALOG_H__
