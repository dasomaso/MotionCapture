/********************************************************************************
** Form generated from reading UI file 'mocap.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOCAP_H
#define UI_MOCAP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MocapClass
{
public:
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MocapClass)
    {
        if (MocapClass->objectName().isEmpty())
            MocapClass->setObjectName(QString::fromUtf8("MocapClass"));
        MocapClass->resize(642, 558);
        centralWidget = new QWidget(MocapClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        MocapClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MocapClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MocapClass->setStatusBar(statusBar);

        retranslateUi(MocapClass);

        QMetaObject::connectSlotsByName(MocapClass);
    } // setupUi

    void retranslateUi(QMainWindow *MocapClass)
    {
        MocapClass->setWindowTitle(QApplication::translate("MocapClass", "Mocap", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MocapClass: public Ui_MocapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOCAP_H
