/********************************************************************************
** Form generated from reading UI file 'scalewidget.ui'
**
** Created: Mon Jan 17 10:48:09 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCALEWIDGET_H
#define UI_SCALEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *zoomToFit;
    QToolButton *zoomOneToOne;
    QSlider *zoomLevel;
    QLabel *currentValue;
    QLabel *label_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(236, 43);
        horizontalLayout = new QHBoxLayout(Form);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        zoomToFit = new QToolButton(Form);
        zoomToFit->setObjectName(QString::fromUtf8("zoomToFit"));

        horizontalLayout->addWidget(zoomToFit);

        zoomOneToOne = new QToolButton(Form);
        zoomOneToOne->setObjectName(QString::fromUtf8("zoomOneToOne"));

        horizontalLayout->addWidget(zoomOneToOne);

        zoomLevel = new QSlider(Form);
        zoomLevel->setObjectName(QString::fromUtf8("zoomLevel"));
        zoomLevel->setMaximum(200);
        zoomLevel->setValue(1);
        zoomLevel->setOrientation(Qt::Horizontal);
        zoomLevel->setTickPosition(QSlider::TicksBothSides);

        horizontalLayout->addWidget(zoomLevel);

        currentValue = new QLabel(Form);
        currentValue->setObjectName(QString::fromUtf8("currentValue"));

        horizontalLayout->addWidget(currentValue);

        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);


        retranslateUi(Form);
        QObject::connect(zoomLevel, SIGNAL(valueChanged(int)), currentValue, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
        zoomToFit->setText(QApplication::translate("Form", "...", 0, QApplication::UnicodeUTF8));
        zoomOneToOne->setText(QApplication::translate("Form", "...", 0, QApplication::UnicodeUTF8));
        currentValue->setText(QApplication::translate("Form", "0", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Form", "%", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCALEWIDGET_H
