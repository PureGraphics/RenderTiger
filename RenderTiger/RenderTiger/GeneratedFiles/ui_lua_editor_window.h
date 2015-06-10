/********************************************************************************
** Form generated from reading UI file 'lua_editor_window.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LUA_EDITOR_WINDOW_H
#define UI_LUA_EDITOR_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_lua_editor_window
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTextEdit *text_editor;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *lua_editor_window)
    {
        if (lua_editor_window->objectName().isEmpty())
            lua_editor_window->setObjectName(QStringLiteral("lua_editor_window"));
        lua_editor_window->resize(600, 600);
        centralwidget = new QWidget(lua_editor_window);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        text_editor = new QTextEdit(centralwidget);
        text_editor->setObjectName(QStringLiteral("text_editor"));
        QFont font;
        font.setFamily(QStringLiteral("Consolas"));
        font.setPointSize(14);
        text_editor->setFont(font);

        horizontalLayout->addWidget(text_editor);

        lua_editor_window->setCentralWidget(centralwidget);
        menubar = new QMenuBar(lua_editor_window);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 23));
        lua_editor_window->setMenuBar(menubar);
        statusbar = new QStatusBar(lua_editor_window);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        lua_editor_window->setStatusBar(statusbar);
        toolBar = new QToolBar(lua_editor_window);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMinimumSize(QSize(0, 30));
        lua_editor_window->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(lua_editor_window);

        QMetaObject::connectSlotsByName(lua_editor_window);
    } // setupUi

    void retranslateUi(QMainWindow *lua_editor_window)
    {
        lua_editor_window->setWindowTitle(QApplication::translate("lua_editor_window", "Lua\347\274\226\350\276\221\347\252\227\345\217\243", 0));
        toolBar->setWindowTitle(QApplication::translate("lua_editor_window", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class lua_editor_window: public Ui_lua_editor_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LUA_EDITOR_WINDOW_H
