/********************************************************************************
** Form generated from reading UI file 'dx11_preview_window.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DX11_PREVIEW_WINDOW_H
#define UI_DX11_PREVIEW_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dx11_preview_window
{
public:
    QWidget *centralwidget;

    void setupUi(QMainWindow *dx11_preview_window)
    {
        if (dx11_preview_window->objectName().isEmpty())
            dx11_preview_window->setObjectName(QStringLiteral("dx11_preview_window"));
        dx11_preview_window->resize(600, 600);
        centralwidget = new QWidget(dx11_preview_window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        dx11_preview_window->setCentralWidget(centralwidget);

        retranslateUi(dx11_preview_window);

        QMetaObject::connectSlotsByName(dx11_preview_window);
    } // setupUi

    void retranslateUi(QMainWindow *dx11_preview_window)
    {
        dx11_preview_window->setWindowTitle(QApplication::translate("dx11_preview_window", "\351\242\204\350\247\210-DX11", 0));
    } // retranslateUi

};

namespace Ui {
    class dx11_preview_window: public Ui_dx11_preview_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DX11_PREVIEW_WINDOW_H
