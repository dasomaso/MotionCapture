/********************************************************************************
** Form generated from reading UI file 'ImageWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEWIDGET_H
#define UI_IMAGEWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtOpenGL/QGLWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageWidget
{
public:

    void setupUi(QGLWidget *ImageWidget)
    {
        if (ImageWidget->objectName().isEmpty())
            ImageWidget->setObjectName(QString::fromUtf8("ImageWidget"));
        ImageWidget->resize(400, 300);

        retranslateUi(ImageWidget);

        QMetaObject::connectSlotsByName(ImageWidget);
    } // setupUi

    void retranslateUi(QGLWidget *ImageWidget)
    {
        ImageWidget->setWindowTitle(QApplication::translate("ImageWidget", "ImageWidget", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ImageWidget: public Ui_ImageWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEWIDGET_H
