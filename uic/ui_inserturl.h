/********************************************************************************
** Form generated from reading UI file 'inserturl.ui'
**
** Created: Wed Jan 19 21:08:26 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTURL_H
#define UI_INSERTURL_H

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

class Ui_InsertUrl
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *urlLineEdit;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *textLineEdit;
    QPushButton *okPushButton;
    QPushButton *cancelPushButton;

    void setupUi(QDialog *InsertUrl)
    {
        if (InsertUrl->objectName().isEmpty())
            InsertUrl->setObjectName(QString::fromUtf8("InsertUrl"));
        InsertUrl->resize(376, 148);
        horizontalLayoutWidget = new QWidget(InsertUrl);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 351, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        urlLineEdit = new QLineEdit(horizontalLayoutWidget);
        urlLineEdit->setObjectName(QString::fromUtf8("urlLineEdit"));

        horizontalLayout->addWidget(urlLineEdit);

        horizontalLayoutWidget_2 = new QWidget(InsertUrl);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 50, 351, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(horizontalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        textLineEdit = new QLineEdit(horizontalLayoutWidget_2);
        textLineEdit->setObjectName(QString::fromUtf8("textLineEdit"));

        horizontalLayout_2->addWidget(textLineEdit);

        okPushButton = new QPushButton(InsertUrl);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));
        okPushButton->setGeometry(QRect(260, 100, 98, 27));
        cancelPushButton = new QPushButton(InsertUrl);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));
        cancelPushButton->setGeometry(QRect(150, 100, 98, 27));

        retranslateUi(InsertUrl);

        QMetaObject::connectSlotsByName(InsertUrl);
    } // setupUi

    void retranslateUi(QDialog *InsertUrl)
    {
        InsertUrl->setWindowTitle(QApplication::translate("InsertUrl", "Insert Url", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("InsertUrl", "Url: ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("InsertUrl", "Text: ", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("InsertUrl", "OK", 0, QApplication::UnicodeUTF8));
        cancelPushButton->setText(QApplication::translate("InsertUrl", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class InsertUrl: public Ui_InsertUrl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTURL_H
