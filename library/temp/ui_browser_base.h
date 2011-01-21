/*
Base widget for the QDomElement node browser.
*/

/********************************************************************************
** Form generated from reading UI file 'browser_base.ui'
**
** Created: Mon Jan 17 10:48:09 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BROWSER_BASE_H
#define UI_BROWSER_BASE_H

#include <Qt3Support/Q3MimeSourceFactory>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NodeBrowserBase
{
public:
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QLabel *textLabel1;
    QLineEdit *path;
    QTreeWidget *nodes;
    QGroupBox *groupBox1;
    QGridLayout *gridLayout;
    QListWidget *properties;
    QHBoxLayout *hboxLayout1;
    QSpacerItem *spacerItem;
    QPushButton *buttonOk;
    QPushButton *buttonCancel;

    void setupUi(QWidget *NodeBrowserBase)
    {
        if (NodeBrowserBase->objectName().isEmpty())
            NodeBrowserBase->setObjectName(QString::fromUtf8("NodeBrowserBase"));
        NodeBrowserBase->resize(399, 342);
        vboxLayout = new QVBoxLayout(NodeBrowserBase);
        vboxLayout->setSpacing(3);
        vboxLayout->setContentsMargins(5, 5, 5, 5);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(3);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        textLabel1 = new QLabel(NodeBrowserBase);
        textLabel1->setObjectName(QString::fromUtf8("textLabel1"));
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1->setWordWrap(false);

        hboxLayout->addWidget(textLabel1);

        path = new QLineEdit(NodeBrowserBase);
        path->setObjectName(QString::fromUtf8("path"));
        QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(0));
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(path->sizePolicy().hasHeightForWidth());
        path->setSizePolicy(sizePolicy);
        path->setReadOnly(true);

        hboxLayout->addWidget(path);


        vboxLayout->addLayout(hboxLayout);

        nodes = new QTreeWidget(NodeBrowserBase);
        nodes->setObjectName(QString::fromUtf8("nodes"));
        QSizePolicy sizePolicy1(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nodes->sizePolicy().hasHeightForWidth());
        nodes->setSizePolicy(sizePolicy1);
        nodes->setRootIsDecorated(true);
        nodes->setAnimated(true);
        nodes->setAllColumnsShowFocus(true);

        vboxLayout->addWidget(nodes);

        groupBox1 = new QGroupBox(NodeBrowserBase);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        groupBox1->setFlat(true);
        gridLayout = new QGridLayout(groupBox1);
        gridLayout->setSpacing(3);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        properties = new QListWidget(groupBox1);
        properties->setObjectName(QString::fromUtf8("properties"));
        sizePolicy1.setHeightForWidth(properties->sizePolicy().hasHeightForWidth());
        properties->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(properties, 0, 0, 1, 1);


        vboxLayout->addWidget(groupBox1);

        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setSpacing(3);
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        spacerItem = new QSpacerItem(191, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout1->addItem(spacerItem);

        buttonOk = new QPushButton(NodeBrowserBase);
        buttonOk->setObjectName(QString::fromUtf8("buttonOk"));

        hboxLayout1->addWidget(buttonOk);

        buttonCancel = new QPushButton(NodeBrowserBase);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        hboxLayout1->addWidget(buttonCancel);


        vboxLayout->addLayout(hboxLayout1);


        retranslateUi(NodeBrowserBase);

        QMetaObject::connectSlotsByName(NodeBrowserBase);
    } // setupUi

    void retranslateUi(QWidget *NodeBrowserBase)
    {
        NodeBrowserBase->setWindowTitle(QApplication::translate("NodeBrowserBase", "Select DOM Path...", 0, QApplication::UnicodeUTF8));
        textLabel1->setText(QApplication::translate("NodeBrowserBase", "Path:", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = nodes->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("NodeBrowserBase", "Nodes", 0, QApplication::UnicodeUTF8));
        groupBox1->setTitle(QApplication::translate("NodeBrowserBase", "Properties", 0, QApplication::UnicodeUTF8));
        buttonOk->setText(QApplication::translate("NodeBrowserBase", "OK", 0, QApplication::UnicodeUTF8));
        buttonCancel->setText(QApplication::translate("NodeBrowserBase", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NodeBrowserBase: public Ui_NodeBrowserBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BROWSER_BASE_H
