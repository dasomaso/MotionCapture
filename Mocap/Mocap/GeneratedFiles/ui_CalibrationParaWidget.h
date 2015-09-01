/********************************************************************************
** Form generated from reading UI file 'CalibrationParaWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONPARAWIDGET_H
#define UI_CALIBRATIONPARAWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationParaWidget
{
public:

    void setupUi(QWidget *CalibrationParaWidget)
    {
        if (CalibrationParaWidget->objectName().isEmpty())
            CalibrationParaWidget->setObjectName(QString::fromUtf8("CalibrationParaWidget"));
        CalibrationParaWidget->resize(400, 300);

        retranslateUi(CalibrationParaWidget);

        QMetaObject::connectSlotsByName(CalibrationParaWidget);
    } // setupUi

    void retranslateUi(QWidget *CalibrationParaWidget)
    {
        CalibrationParaWidget->setWindowTitle(QApplication::translate("CalibrationParaWidget", "CalibrationParaWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalibrationParaWidget: public Ui_CalibrationParaWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONPARAWIDGET_H
