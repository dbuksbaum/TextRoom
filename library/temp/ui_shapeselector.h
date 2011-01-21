/********************************************************************************
** Form generated from reading UI file 'shapeselector.ui'
**
** Created: Mon Jan 17 10:48:09 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAPESELECTOR_H
#define UI_SHAPESELECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ShapeSelector
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *label;
    QComboBox *shapeType;
    QGroupBox *groupBox;
    QVBoxLayout *vboxLayout1;
    QLabel *shapePreview;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ShapeSelector)
    {
        if (ShapeSelector->objectName().isEmpty())
            ShapeSelector->setObjectName(QString::fromUtf8("ShapeSelector"));
        ShapeSelector->resize(296, 260);
        vboxLayout = new QVBoxLayout(ShapeSelector);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label = new QLabel(ShapeSelector);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        shapeType = new QComboBox(ShapeSelector);
        shapeType->setObjectName(QString::fromUtf8("shapeType"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(shapeType->sizePolicy().hasHeightForWidth());
        shapeType->setSizePolicy(sizePolicy);

        hboxLayout->addWidget(shapeType);


        vboxLayout->addLayout(hboxLayout);

        groupBox = new QGroupBox(ShapeSelector);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        vboxLayout1 = new QVBoxLayout(groupBox);
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        shapePreview = new QLabel(groupBox);
        shapePreview->setObjectName(QString::fromUtf8("shapePreview"));
        shapePreview->setMinimumSize(QSize(256, 128));
        shapePreview->setPixmap(QPixmap(QString::fromUtf8(":/images/background.png")));
        shapePreview->setScaledContents(false);

        vboxLayout1->addWidget(shapePreview);


        vboxLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(ShapeSelector);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        vboxLayout->addWidget(buttonBox);


        retranslateUi(ShapeSelector);
        QObject::connect(buttonBox, SIGNAL(accepted()), ShapeSelector, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ShapeSelector, SLOT(reject()));

        QMetaObject::connectSlotsByName(ShapeSelector);
    } // setupUi

    void retranslateUi(QDialog *ShapeSelector)
    {
        ShapeSelector->setWindowTitle(QApplication::translate("ShapeSelector", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ShapeSelector", "Type:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("ShapeSelector", "Preview:", 0, QApplication::UnicodeUTF8));
        shapePreview->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ShapeSelector: public Ui_ShapeSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAPESELECTOR_H
