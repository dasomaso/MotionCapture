/********************************************************************************
** Form generated from reading UI file 'POISemanticSelectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POISEMANTICSELECTIONDIALOG_H
#define UI_POISEMANTICSELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_POISemanticSelectionDialog
{
public:

    void setupUi(QDialog *POISemanticSelectionDialog)
    {
        if (POISemanticSelectionDialog->objectName().isEmpty())
            POISemanticSelectionDialog->setObjectName(QString::fromUtf8("POISemanticSelectionDialog"));
        POISemanticSelectionDialog->resize(400, 300);

        retranslateUi(POISemanticSelectionDialog);

        QMetaObject::connectSlotsByName(POISemanticSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *POISemanticSelectionDialog)
    {
        POISemanticSelectionDialog->setWindowTitle(QApplication::translate("POISemanticSelectionDialog", "POISemanticSelectionDialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class POISemanticSelectionDialog: public Ui_POISemanticSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POISEMANTICSELECTIONDIALOG_H
