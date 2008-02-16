#ifndef __FINDDIALOG_H__
#define __FINDDIALOG_H__

#include <QDialog>

class QCheckBox;
class QDialogButtonBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;

class SearchDialog : public QDialog
{
	Q_OBJECT

public:
	SearchDialog(QWidget *parent = 0,
			const QString &lstSearch = QString());
	static QString useSearchDialog(QWidget *parent = 0,
					const QString &srchString = QString());

private:
	QLabel *label;
	QLineEdit *lineEdit;
	QCheckBox *caseCheckBox;
	QCheckBox *wholeWordsCheckBox;
	QCheckBox *backwardCheckBox;
	QDialogButtonBox *buttonBox;
	QPushButton *findButton;
	QPushButton *cancelButton;

};

#endif
