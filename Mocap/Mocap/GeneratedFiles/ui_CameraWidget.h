/********************************************************************************
** Form generated from reading UI file 'CameraWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAWIDGET_H
#define UI_CAMERAWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraWidget
{
public:

    void setupUi(QWidget *CameraWidget)
    {
        if (CameraWidget->objectName().isEmpty())
            CameraWidget->setObjectName(QString::fromUtf8("CameraWidget"));
        CameraWidget->resize(400, 300);

        retranslateUi(CameraWidget);

        QMetaObject::connectSlotsByName(CameraWidget);
    } // setupUi

    void retranslateUi(QWidget *CameraWidget)
    {
        CameraWidget->setWindowTitle(QApplication::translate("CameraWidget", "CameraWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CameraWidget: public Ui_CameraWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAWIDGET_H
