/********************************************************************************
** Form generated from reading UI file 'ThreeDWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THREEDWIDGET_H
#define UI_THREEDWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtOpenGL/QGLWidget>

QT_BEGIN_NAMESPACE

class Ui_ThreeDWidget
{
public:

    void setupUi(QGLWidget *ThreeDWidget)
    {
        if (ThreeDWidget->objectName().isEmpty())
            ThreeDWidget->setObjectName(QString::fromUtf8("ThreeDWidget"));
        ThreeDWidget->resize(400, 300);

        retranslateUi(ThreeDWidget);

        QMetaObject::connectSlotsByName(ThreeDWidget);
    } // setupUi

    void retranslateUi(QGLWidget *ThreeDWidget)
    {
        ThreeDWidget->setWindowTitle(QApplication::translate("ThreeDWidget", "ThreeDWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ThreeDWidget: public Ui_ThreeDWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THREEDWIDGET_H
