/********************************************************************************
** Form generated from reading UI file 'ReconstructionParaWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECONSTRUCTIONPARAWIDGET_H
#define UI_RECONSTRUCTIONPARAWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReconstructionParaWidget
{
public:

    void setupUi(QWidget *ReconstructionParaWidget)
    {
        if (ReconstructionParaWidget->objectName().isEmpty())
            ReconstructionParaWidget->setObjectName(QString::fromUtf8("ReconstructionParaWidget"));
        ReconstructionParaWidget->resize(400, 300);

        retranslateUi(ReconstructionParaWidget);

        QMetaObject::connectSlotsByName(ReconstructionParaWidget);
    } // setupUi

    void retranslateUi(QWidget *ReconstructionParaWidget)
    {
        ReconstructionParaWidget->setWindowTitle(QApplication::translate("ReconstructionParaWidget", "ReconstructionParaWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReconstructionParaWidget: public Ui_ReconstructionParaWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECONSTRUCTIONPARAWIDGET_H
