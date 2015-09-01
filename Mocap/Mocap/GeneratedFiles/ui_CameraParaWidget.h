/********************************************************************************
** Form generated from reading UI file 'CameraParaWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAPARAWIDGET_H
#define UI_CAMERAPARAWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraParaWidget
{
public:

    void setupUi(QWidget *CameraParaWidget)
    {
        if (CameraParaWidget->objectName().isEmpty())
            CameraParaWidget->setObjectName(QString::fromUtf8("CameraParaWidget"));
        CameraParaWidget->resize(400, 300);

        retranslateUi(CameraParaWidget);

        QMetaObject::connectSlotsByName(CameraParaWidget);
    } // setupUi

    void retranslateUi(QWidget *CameraParaWidget)
    {
        CameraParaWidget->setWindowTitle(QApplication::translate("CameraParaWidget", "CameraParaWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CameraParaWidget: public Ui_CameraParaWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAPARAWIDGET_H
