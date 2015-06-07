#ifndef dx11_fx_editor_window_h
#define dx11_fx_editor_window_h

#include <QMainWindow>
#include <QList>
#include <QString>

#include "ui_dx11_fx_editor_window.h"

class dx11_fx_editor_window : public QMainWindow {
    Q_OBJECT
public:
    dx11_fx_editor_window(QWidget *parent);
    ~dx11_fx_editor_window();
protected: //Qt inner methods.
    void closeEvent(QCloseEvent *event);
private:
    void _init_keywords();
    void _init_events();
private slots:
    void _on_contents_changed();
private:
    Ui::dx11_fx_editor_window _ui;
    QWidget *_parent;

    QList<QString> _keywords;
    QString _curr_text;
    QString _prev_text;
};

#endif