/********************************************************************************
** Form generated from reading UI file 'EvaluationWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EVALUATIONWIDGET_H
#define UI_EVALUATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EvaluationWidget
{
public:

    void setupUi(QWidget *EvaluationWidget)
    {
        if (EvaluationWidget->objectName().isEmpty())
            EvaluationWidget->setObjectName(QString::fromUtf8("EvaluationWidget"));
        EvaluationWidget->resize(400, 300);

        retranslateUi(EvaluationWidget);

        QMetaObject::connectSlotsByName(EvaluationWidget);
    } // setupUi

    void retranslateUi(QWidget *EvaluationWidget)
    {
        EvaluationWidget->setWindowTitle(QApplication::translate("EvaluationWidget", "EvaluationWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class EvaluationWidget: public Ui_EvaluationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EVALUATIONWIDGET_H
