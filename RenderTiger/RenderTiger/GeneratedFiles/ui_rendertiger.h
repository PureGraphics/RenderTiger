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
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_render_tiger_main_window_ui
{
public:
    QAction *actionTest;
    QAction *actionHello;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionWorkspace;
    QAction *actionOutput;
    QAction *actionPreview;
    QAction *actionCompile;
    QAction *actionShader_fx;
    QAction *actionLua;
    QAction *actionAbout;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QMdiArea *mdiArea;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QToolBar *toolBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;

    void setupUi(QMainWindow *render_tiger_main_window_ui)
    {
        if (render_tiger_main_window_ui->objectName().isEmpty())
            render_tiger_main_window_ui->setObjectName(QStringLiteral("render_tiger_main_window_ui"));
        render_tiger_main_window_ui->resize(1003, 928);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(50);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(render_tiger_main_window_ui->sizePolicy().hasHeightForWidth());
        render_tiger_main_window_ui->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/RenderTiger/Logo"), QSize(), QIcon::Normal, QIcon::Off);
        render_tiger_main_window_ui->setWindowIcon(icon);
        render_tiger_main_window_ui->setAutoFillBackground(true);
        actionTest = new QAction(render_tiger_main_window_ui);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionHello = new QAction(render_tiger_main_window_ui);
        actionHello->setObjectName(QStringLiteral("actionHello"));
        actionOpen = new QAction(render_tiger_main_window_ui);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(render_tiger_main_window_ui);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExit = new QAction(render_tiger_main_window_ui);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionWorkspace = new QAction(render_tiger_main_window_ui);
        actionWorkspace->setObjectName(QStringLiteral("actionWorkspace"));
        actionOutput = new QAction(render_tiger_main_window_ui);
        actionOutput->setObjectName(QStringLiteral("actionOutput"));
        actionPreview = new QAction(render_tiger_main_window_ui);
        actionPreview->setObjectName(QStringLiteral("actionPreview"));
        actionPreview->setCheckable(true);
        actionCompile = new QAction(render_tiger_main_window_ui);
        actionCompile->setObjectName(QStringLiteral("actionCompile"));
        actionCompile->setIcon(icon);
        actionShader_fx = new QAction(render_tiger_main_window_ui);
        actionShader_fx->setObjectName(QStringLiteral("actionShader_fx"));
        actionShader_fx->setCheckable(true);
        actionLua = new QAction(render_tiger_main_window_ui);
        actionLua->setObjectName(QStringLiteral("actionLua"));
        actionLua->setCheckable(true);
        actionAbout = new QAction(render_tiger_main_window_ui);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(render_tiger_main_window_ui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        horizontalLayout->addWidget(mdiArea);

        render_tiger_main_window_ui->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(render_tiger_main_window_ui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        render_tiger_main_window_ui->setStatusBar(statusBar);
        menuBar = new QMenuBar(render_tiger_main_window_ui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1003, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        render_tiger_main_window_ui->setMenuBar(menuBar);
        toolBar = new QToolBar(render_tiger_main_window_ui);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMinimumSize(QSize(0, 30));
        render_tiger_main_window_ui->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget = new QDockWidget(render_tiger_main_window_ui);
        dockWidget->setObjectName(QStringLiteral("dockWidget"));
        dockWidget->setMinimumSize(QSize(200, 38));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        dockWidget->setWidget(dockWidgetContents);
        render_tiger_main_window_ui->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);
        dockWidget_2 = new QDockWidget(render_tiger_main_window_ui);
        dockWidget_2->setObjectName(QStringLiteral("dockWidget_2"));
        dockWidget_2->setMinimumSize(QSize(80, 120));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        dockWidget_2->setWidget(dockWidgetContents_2);
        render_tiger_main_window_ui->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidget_2);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu_3->addAction(actionShader_fx);
        menu_3->addAction(actionLua);
        menu_3->addAction(actionPreview);
        menu_4->addAction(actionAbout);
        toolBar->addAction(actionCompile);
        toolBar->addSeparator();

        retranslateUi(render_tiger_main_window_ui);

        QMetaObject::connectSlotsByName(render_tiger_main_window_ui);
    } // setupUi

    void retranslateUi(QMainWindow *render_tiger_main_window_ui)
    {
        render_tiger_main_window_ui->setWindowTitle(QApplication::translate("render_tiger_main_window_ui", "RenderTiger", 0));
        actionTest->setText(QApplication::translate("render_tiger_main_window_ui", "test", 0));
        actionHello->setText(QApplication::translate("render_tiger_main_window_ui", "Hello", 0));
        actionOpen->setText(QApplication::translate("render_tiger_main_window_ui", "Open", 0));
        actionSave->setText(QApplication::translate("render_tiger_main_window_ui", "Save", 0));
        actionExit->setText(QApplication::translate("render_tiger_main_window_ui", "Exit", 0));
        actionWorkspace->setText(QApplication::translate("render_tiger_main_window_ui", "Workspace", 0));
        actionOutput->setText(QApplication::translate("render_tiger_main_window_ui", "Output", 0));
        actionPreview->setText(QApplication::translate("render_tiger_main_window_ui", "\351\242\204\350\247\210", 0));
        actionCompile->setText(QApplication::translate("render_tiger_main_window_ui", "\347\274\226\350\257\221", 0));
        actionCompile->setIconText(QApplication::translate("render_tiger_main_window_ui", "\347\274\226\350\257\221", 0));
#ifndef QT_NO_TOOLTIP
        actionCompile->setToolTip(QApplication::translate("render_tiger_main_window_ui", "\347\274\226\350\257\221", 0));
#endif // QT_NO_TOOLTIP
        actionShader_fx->setText(QApplication::translate("render_tiger_main_window_ui", "\347\274\226\350\276\221Shader(FX)", 0));
        actionLua->setText(QApplication::translate("render_tiger_main_window_ui", "\347\274\226\350\276\221Lua", 0));
        actionAbout->setText(QApplication::translate("render_tiger_main_window_ui", "\345\205\263\344\272\216", 0));
        menu->setTitle(QApplication::translate("render_tiger_main_window_ui", "\346\226\207\344\273\266", 0));
        menu_2->setTitle(QApplication::translate("render_tiger_main_window_ui", "\347\274\226\350\276\221", 0));
        menu_3->setTitle(QApplication::translate("render_tiger_main_window_ui", "\350\247\206\345\233\276", 0));
        menu_4->setTitle(QApplication::translate("render_tiger_main_window_ui", "\345\270\256\345\212\251", 0));
        toolBar->setWindowTitle(QApplication::translate("render_tiger_main_window_ui", "toolBar", 0));
        dockWidget->setWindowTitle(QApplication::translate("render_tiger_main_window_ui", "\345\267\245\344\275\234\347\251\272\351\227\264", 0));
        dockWidget_2->setWindowTitle(QApplication::translate("render_tiger_main_window_ui", "\350\276\223\345\207\272", 0));
    } // retranslateUi

};

namespace Ui {
    class render_tiger_main_window_ui: public Ui_render_tiger_main_window_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERTIGER_H
