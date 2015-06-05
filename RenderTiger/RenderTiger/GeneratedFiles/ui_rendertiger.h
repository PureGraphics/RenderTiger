/********************************************************************************
** Form generated from reading UI file 'rendertiger.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERTIGER_H
#define UI_RENDERTIGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RenderTigerClass
{
public:
    QAction *actionTest;
    QAction *actionHello;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RenderTigerClass)
    {
        if (RenderTigerClass->objectName().isEmpty())
            RenderTigerClass->setObjectName(QStringLiteral("RenderTigerClass"));
        RenderTigerClass->resize(996, 928);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(50);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RenderTigerClass->sizePolicy().hasHeightForWidth());
        RenderTigerClass->setSizePolicy(sizePolicy);
        RenderTigerClass->setAutoFillBackground(true);
        actionTest = new QAction(RenderTigerClass);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionHello = new QAction(RenderTigerClass);
        actionHello->setObjectName(QStringLiteral("actionHello"));
        actionOpen = new QAction(RenderTigerClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(RenderTigerClass);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(RenderTigerClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(RenderTigerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        RenderTigerClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(RenderTigerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RenderTigerClass->setStatusBar(statusBar);

        retranslateUi(RenderTigerClass);

        QMetaObject::connectSlotsByName(RenderTigerClass);
    } // setupUi

    void retranslateUi(QMainWindow *RenderTigerClass)
    {
        RenderTigerClass->setWindowTitle(QApplication::translate("RenderTigerClass", "RenderTiger", 0));
        actionTest->setText(QApplication::translate("RenderTigerClass", "test", 0));
        actionHello->setText(QApplication::translate("RenderTigerClass", "Hello", 0));
        actionOpen->setText(QApplication::translate("RenderTigerClass", "Open", 0));
        actionSave->setText(QApplication::translate("RenderTigerClass", "Save", 0));
        actionExit->setText(QApplication::translate("RenderTigerClass", "Exit", 0));
    } // retranslateUi

};

namespace Ui {
    class RenderTigerClass: public Ui_RenderTigerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERTIGER_H
