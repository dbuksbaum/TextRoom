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
	void activateApply();
    void on_pushButtonOK_clicked();
	void on_pushButtonApply_clicked();
	void on_pbEditorColor_clicked();
	void on_pbEditorBackColor_clicked();
	void on_pbStatusBarColor_clicked();
	void showForegroundDialog();
	void showBackgroundDialog();
	void showStatusColorDialog();

private:
	QColor fgcolor;
	QColor bgcolor;
	QColor scolor;

private:

    Ui::OptionsDialog ui;

protected:
    void showEvent( QShowEvent * );
};

#endif // __OPTIONSDIALOG_H__
