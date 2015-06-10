#ifndef lua_editor_window_h
#define lua_editor_window_h

#include <QMainWindow>
#include <QList>
#include <QString>

#include "ui_lua_editor_window.h"

class lua_editor_window : public QMainWindow {
    Q_OBJECT
public:
    lua_editor_window(QWidget *parent);
    ~lua_editor_window();
public:
    QString get_lua_src();
protected: //Qt inner methods.
    void closeEvent(QCloseEvent *event);
private:
    void _init_keywords();
    void _init_events();
private slots:
    void _on_contents_changed();
private:
    Ui::lua_editor_window _ui;
    QWidget *_parent;

    QList<QString> _keywords;
    QString _curr_text;
    QString _prev_text;
};

#endif