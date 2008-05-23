#ifndef __HELPDIALOG_H__
#define __HELPDIALOG_H__

#include <QtGui>
#include <QWidget>

#include "ui_helpdialog.h"

class TextRoom;

class HelpDialog: public QDialog, public Ui::HelpDialog
{
	Q_OBJECT
	
public:
	HelpDialog(QWidget *parent = 0);

private:
	Ui::HelpDialog ui;

};

#endif


