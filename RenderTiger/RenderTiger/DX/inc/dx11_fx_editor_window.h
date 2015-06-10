#ifndef dx11_fx_editor_window_h
#define dx11_fx_editor_window_h

#include <QMainWindow>
#include <QList>
#include <QString>

#include "ui_dx11_fx_editor_window.h"
#include "base_text_editor.h"

class dx11_fx_editor_window : public QMainWindow, public base_text_editor {
    Q_OBJECT
public:
    dx11_fx_editor_window(QWidget *parent);
    ~dx11_fx_editor_window();
public:
    QString get_fx_src();
protected: //Qt inner methods.
    void closeEvent(QCloseEvent *event);
protected:
    void _init_keywords() override;
private:
    void _init_events();
private slots:
    void _on_contents_changed();
private:
    Ui::dx11_fx_editor_window _ui;
    QWidget *_parent;

    QString _curr_text;
    QString _prev_text;
};

#endif