/********************************************************************************
** Form generated from reading UI file 'CalibrationWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONWIDGET_H
#define UI_CALIBRATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationWidget
{
public:

    void setupUi(QWidget *CalibrationWidget)
    {
        if (CalibrationWidget->objectName().isEmpty())
            CalibrationWidget->setObjectName(QString::fromUtf8("CalibrationWidget"));
        CalibrationWidget->resize(400, 300);

        retranslateUi(CalibrationWidget);

        QMetaObject::connectSlotsByName(CalibrationWidget);
    } // setupUi

    void retranslateUi(QWidget *CalibrationWidget)
    {
        CalibrationWidget->setWindowTitle(QApplication::translate("CalibrationWidget", "CalibrationWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalibrationWidget: public Ui_CalibrationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONWIDGET_H
