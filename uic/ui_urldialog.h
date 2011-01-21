/********************************************************************************
** Form generated from reading UI file 'urldialog.ui'
**
** Created: Thu Jan 20 06:57:12 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_URLDIALOG_H
#define UI_URLDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UrlDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *urlLineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *UrlDialog)
    {
        if (UrlDialog->objectName().isEmpty())
            UrlDialog->setObjectName(QString::fromUtf8("UrlDialog"));
        UrlDialog->resize(329, 87);
        UrlDialog->setLayoutDirection(Qt::LeftToRight);
        UrlDialog->setAutoFillBackground(true);
        horizontalLayoutWidget = new QWidget(UrlDialog);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 311, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        urlLineEdit = new QLineEdit(horizontalLayoutWidget);
        urlLineEdit->setObjectName(QString::fromUtf8("urlLineEdit"));

        horizontalLayout->addWidget(urlLineEdit);

        okButton = new QPushButton(UrlDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(220, 50, 98, 27));
        cancelButton = new QPushButton(UrlDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(110, 50, 98, 27));

        retranslateUi(UrlDialog);

        QMetaObject::connectSlotsByName(UrlDialog);
    } // setupUi

    void retranslateUi(QDialog *UrlDialog)
    {
        UrlDialog->setWindowTitle(QApplication::translate("UrlDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UrlDialog", "Url :", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("UrlDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("UrlDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UrlDialog: public Ui_UrlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_URLDIALOG_H
