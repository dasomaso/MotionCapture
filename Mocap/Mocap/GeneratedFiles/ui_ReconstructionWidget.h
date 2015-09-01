/********************************************************************************
** Form generated from reading UI file 'ReconstructionWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECONSTRUCTIONWIDGET_H
#define UI_RECONSTRUCTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReconstructionWidget
{
public:

    void setupUi(QWidget *ReconstructionWidget)
    {
        if (ReconstructionWidget->objectName().isEmpty())
            ReconstructionWidget->setObjectName(QString::fromUtf8("ReconstructionWidget"));
        ReconstructionWidget->resize(400, 300);

        retranslateUi(ReconstructionWidget);

        QMetaObject::connectSlotsByName(ReconstructionWidget);
    } // setupUi

    void retranslateUi(QWidget *ReconstructionWidget)
    {
        ReconstructionWidget->setWindowTitle(QApplication::translate("ReconstructionWidget", "ReconstructionWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReconstructionWidget: public Ui_ReconstructionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECONSTRUCTIONWIDGET_H
