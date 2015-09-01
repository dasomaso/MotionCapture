/********************************************************************************
** Form generated from reading UI file 'PostprocessWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTPROCESSWIDGET_H
#define UI_POSTPROCESSWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PostprocessWidget
{
public:

    void setupUi(QWidget *PostprocessWidget)
    {
        if (PostprocessWidget->objectName().isEmpty())
            PostprocessWidget->setObjectName(QString::fromUtf8("PostprocessWidget"));
        PostprocessWidget->resize(400, 300);

        retranslateUi(PostprocessWidget);

        QMetaObject::connectSlotsByName(PostprocessWidget);
    } // setupUi

    void retranslateUi(QWidget *PostprocessWidget)
    {
        PostprocessWidget->setWindowTitle(QApplication::translate("PostprocessWidget", "PostprocessWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PostprocessWidget: public Ui_PostprocessWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTPROCESSWIDGET_H
