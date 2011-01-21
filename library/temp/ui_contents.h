/********************************************************************************
** Form generated from reading UI file 'contents.ui'
**
** Created: Mon Jan 17 10:48:09 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTENTS_H
#define UI_CONTENTS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFontComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "colorbutton.h"
#include "plaintextedit.h"

QT_BEGIN_NAMESPACE

class Ui_ContentsWidget
{
public:
    QVBoxLayout *vboxLayout;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout;
    QLabel *label_10;
    QLineEdit *objectTitle;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QLabel *label_11;
    QSpinBox *objectOrder;
    QSpacerItem *spacerItem;
    QLabel *label;
    ColorButton *objectColor;
    QSpacerItem *spacerItem1;
    QLabel *label_2;
    QFontComboBox *objectFont;
    QLabel *label_4;
    QComboBox *shapeSelection;
    QGroupBox *notes;
    QVBoxLayout *vboxLayout2;
    PlainTextEdit *objectText;
    QWidget *tab_2;
    QVBoxLayout *vboxLayout3;
    QTableView *propertyEditor;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ContentsWidget)
    {
        if (ContentsWidget->objectName().isEmpty())
            ContentsWidget->setObjectName(QString::fromUtf8("ContentsWidget"));
        ContentsWidget->resize(571, 571);
        vboxLayout = new QVBoxLayout(ContentsWidget);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label_10 = new QLabel(ContentsWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout->addWidget(label_10);

        objectTitle = new QLineEdit(ContentsWidget);
        objectTitle->setObjectName(QString::fromUtf8("objectTitle"));
        objectTitle->setMinimumSize(QSize(300, 0));

        hboxLayout->addWidget(objectTitle);


        vboxLayout1->addLayout(hboxLayout);


        vboxLayout->addLayout(vboxLayout1);

        tabWidget = new QTabWidget(ContentsWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_11 = new QLabel(tab);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 0, 0, 1, 1);

        objectOrder = new QSpinBox(tab);
        objectOrder->setObjectName(QString::fromUtf8("objectOrder"));
        objectOrder->setWrapping(true);
        objectOrder->setMaximum(1);

        gridLayout->addWidget(objectOrder, 0, 1, 1, 1);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem, 0, 2, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        objectColor = new ColorButton(tab);
        objectColor->setObjectName(QString::fromUtf8("objectColor"));

        gridLayout->addWidget(objectColor, 1, 1, 1, 1);

        spacerItem1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(spacerItem1, 1, 2, 1, 1);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        objectFont = new QFontComboBox(tab);
        objectFont->setObjectName(QString::fromUtf8("objectFont"));

        gridLayout->addWidget(objectFont, 2, 1, 1, 2);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        shapeSelection = new QComboBox(tab);
        shapeSelection->setObjectName(QString::fromUtf8("shapeSelection"));

        gridLayout->addWidget(shapeSelection, 3, 1, 1, 2);

        notes = new QGroupBox(tab);
        notes->setObjectName(QString::fromUtf8("notes"));
        vboxLayout2 = new QVBoxLayout(notes);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        objectText = new PlainTextEdit(notes);
        objectText->setObjectName(QString::fromUtf8("objectText"));
        objectText->setAcceptRichText(false);

        vboxLayout2->addWidget(objectText);


        gridLayout->addWidget(notes, 4, 0, 1, 3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        vboxLayout3 = new QVBoxLayout(tab_2);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        propertyEditor = new QTableView(tab_2);
        propertyEditor->setObjectName(QString::fromUtf8("propertyEditor"));

        vboxLayout3->addWidget(propertyEditor);

        tabWidget->addTab(tab_2, QString());

        vboxLayout->addWidget(tabWidget);

        buttonBox = new QDialogButtonBox(ContentsWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Close);

        vboxLayout->addWidget(buttonBox);

        QWidget::setTabOrder(objectTitle, objectOrder);
        QWidget::setTabOrder(objectOrder, objectText);

        retranslateUi(ContentsWidget);
        QObject::connect(buttonBox, SIGNAL(accepted()), ContentsWidget, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ContentsWidget, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ContentsWidget);
    } // setupUi

    void retranslateUi(QDialog *ContentsWidget)
    {
        ContentsWidget->setWindowTitle(QApplication::translate("ContentsWidget", "Form", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("ContentsWidget", "Title:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("ContentsWidget", "Index:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ContentsWidget", "Color:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ContentsWidget", "Font:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ContentsWidget", "Shape:", 0, QApplication::UnicodeUTF8));
        notes->setTitle(QApplication::translate("ContentsWidget", "Notes:", 0, QApplication::UnicodeUTF8));
        objectText->setHtml(QApplication::translate("ContentsWidget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'Sans Serif'; font-size:9pt;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ContentsWidget", "Properties", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ContentsWidget", "Advanced", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ContentsWidget: public Ui_ContentsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTENTS_H
