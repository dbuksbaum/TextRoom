/********************************************************************************
** Form generated from reading UI file 'asciiexport.ui'
**
** Created: Mon Jan 17 10:48:09 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASCIIEXPORT_H
#define UI_ASCIIEXPORT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ASCIIExportDialog
{
public:
    QVBoxLayout *vboxLayout;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QTextBrowser *preview;
    QHBoxLayout *hboxLayout;
    QLabel *label_2;
    QSpinBox *tabSize;
    QLabel *label_3;
    QSpinBox *pgCols;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout1;
    QLabel *label;
    QLineEdit *filePath;
    QToolButton *selectFile;
    QHBoxLayout *hboxLayout2;
    QSpacerItem *spacerItem1;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QDialog *ASCIIExportDialog)
    {
        if (ASCIIExportDialog->objectName().isEmpty())
            ASCIIExportDialog->setObjectName(QString::fromUtf8("ASCIIExportDialog"));
        ASCIIExportDialog->resize(522, 450);
        ASCIIExportDialog->setSizeGripEnabled(true);
        vboxLayout = new QVBoxLayout(ASCIIExportDialog);
        vboxLayout->setSpacing(6);
        vboxLayout->setContentsMargins(9, 9, 9, 9);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        groupBox = new QGroupBox(ASCIIExportDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setSpacing(6);
        vboxLayout1->setContentsMargins(9, 9, 9, 9);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        preview = new QTextBrowser(groupBox);
        preview->setObjectName(QString::fromUtf8("preview"));
        preview->setLineWrapMode(QTextEdit::FixedColumnWidth);
        preview->setLineWrapColumnOrWidth(80);
        preview->setAcceptRichText(false);

        vboxLayout1->addWidget(preview);


        vboxLayout->addWidget(groupBox);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label_2 = new QLabel(ASCIIExportDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        hboxLayout->addWidget(label_2);

        tabSize = new QSpinBox(ASCIIExportDialog);
        tabSize->setObjectName(QString::fromUtf8("tabSize"));
        tabSize->setMaximum(10);
        tabSize->setMinimum(1);
        tabSize->setValue(5);

        hboxLayout->addWidget(tabSize);

        label_3 = new QLabel(ASCIIExportDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        hboxLayout->addWidget(label_3);

        pgCols = new QSpinBox(ASCIIExportDialog);
        pgCols->setObjectName(QString::fromUtf8("pgCols"));
        pgCols->setMaximum(100);
        pgCols->setMinimum(25);
        pgCols->setValue(80);

        hboxLayout->addWidget(pgCols);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(6);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        label = new QLabel(ASCIIExportDialog);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout1->addWidget(label);

        filePath = new QLineEdit(ASCIIExportDialog);
        filePath->setObjectName(QString::fromUtf8("filePath"));

        hboxLayout1->addWidget(filePath);

        selectFile = new QToolButton(ASCIIExportDialog);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));
        const QIcon icon = QIcon(QString::fromUtf8(":/library/icons/document-open.svg"));
        selectFile->setIcon(icon);

        hboxLayout1->addWidget(selectFile);


        vboxLayout->addLayout(hboxLayout1);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setSpacing(6);
        hboxLayout2->setContentsMargins(0, 0, 0, 0);
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout2->addItem(spacerItem1);

        buttonOk = new QPushButton(ASCIIExportDialog);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));
        buttonOk->setAutoDefault(true);
        buttonOk->setDefault(true);

        hboxLayout2->addWidget(buttonOk);

        buttonCancel = new QPushButton(ASCIIExportDialog);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));
        buttonCancel->setAutoDefault(true);

        hboxLayout2->addWidget(buttonCancel);


        vboxLayout->addLayout(hboxLayout2);


        retranslateUi(ASCIIExportDialog);
        QObject::connect(buttonOk, SIGNAL(clicked()), ASCIIExportDialog, SLOT(accept()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), ASCIIExportDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ASCIIExportDialog);
    } // setupUi

    void retranslateUi(QDialog *ASCIIExportDialog)
    {
        ASCIIExportDialog->setWindowTitle(QApplication::translate("ASCIIExportDialog", "ASCII Document Export", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ASCIIExportDialog", "Preview", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ASCIIExportDialog", "Tab size:", 0, QApplication::UnicodeUTF8));
        tabSize->setSuffix(QApplication::translate("ASCIIExportDialog", "spaces", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ASCIIExportDialog", "Page width:", 0, QApplication::UnicodeUTF8));
        pgCols->setSuffix(QApplication::translate("ASCIIExportDialog", "cols", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ASCIIExportDialog", "Export File:", 0, QApplication::UnicodeUTF8));
        selectFile->setText(QApplication::translate("ASCIIExportDialog", "...", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("ASCIIExportDialog", "&OK", 0, QApplication::UnicodeUTF8));
        buttonOk->setShortcut(QString());
        buttonCancel->setText(QApplication::translate("ASCIIExportDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        buttonCancel->setShortcut(QString());
    } // retranslateUi

};

namespace Ui {
    class ASCIIExportDialog: public Ui_ASCIIExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASCIIEXPORT_H
