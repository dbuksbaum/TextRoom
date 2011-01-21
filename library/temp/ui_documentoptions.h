/********************************************************************************
** Form generated from reading UI file 'documentoptions.ui'
**
** Created: Mon Jan 17 10:48:09 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCUMENTOPTIONS_H
#define UI_DOCUMENTOPTIONS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include "plaintextedit.h"

QT_BEGIN_NAMESPACE

class Ui_DocumentOptions
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QGridLayout *gridLayout;
    QLabel *label_5;
    QLabel *label;
    QLineEdit *documentAuthor;
    QLabel *label_2;
    QLineEdit *documentTitle;
    PlainTextEdit *documentDescription;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DocumentOptions)
    {
        if (DocumentOptions->objectName().isEmpty())
            DocumentOptions->setObjectName(QString::fromUtf8("DocumentOptions"));
        DocumentOptions->resize(416, 295);
        DocumentOptions->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(DocumentOptions);
        vboxLayout->setSpacing(6);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox = new QGroupBox(DocumentOptions);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTop|Qt::AlignTrailing);

        gridLayout->addWidget(label_5, 2, 0, 3, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        documentAuthor = new QLineEdit(groupBox);
        documentAuthor->setObjectName(QString::fromUtf8("documentAuthor"));

        gridLayout->addWidget(documentAuthor, 1, 1, 1, 4);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        documentTitle = new QLineEdit(groupBox);
        documentTitle->setObjectName(QString::fromUtf8("documentTitle"));

        gridLayout->addWidget(documentTitle, 0, 1, 1, 4);

        documentDescription = new PlainTextEdit(groupBox);
        documentDescription->setObjectName(QString::fromUtf8("documentDescription"));

        gridLayout->addWidget(documentDescription, 2, 1, 3, 4);


        vboxLayout1->addLayout(gridLayout);


        vboxLayout->addWidget(groupBox);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(DocumentOptions);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(DocumentOptions);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        vboxLayout->addLayout(hboxLayout);

        QWidget::setTabOrder(documentTitle, documentAuthor);
        QWidget::setTabOrder(documentAuthor, documentDescription);
        QWidget::setTabOrder(documentDescription, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(DocumentOptions);
        QObject::connect(okButton, SIGNAL(clicked()), DocumentOptions, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), DocumentOptions, SLOT(reject()));

        QMetaObject::connectSlotsByName(DocumentOptions);
    } // setupUi

    void retranslateUi(QDialog *DocumentOptions)
    {
        DocumentOptions->setWindowTitle(QApplication::translate("DocumentOptions", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DocumentOptions", "Document Options", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("DocumentOptions", "Description:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DocumentOptions", "Title:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DocumentOptions", "Author:", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("DocumentOptions", "OK", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("DocumentOptions", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DocumentOptions: public Ui_DocumentOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCUMENTOPTIONS_H
