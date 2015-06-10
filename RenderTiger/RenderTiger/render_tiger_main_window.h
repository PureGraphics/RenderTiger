#ifndef RENDERTIGER_H
#define RENDERTIGER_H

#include <QMainWindow>
#include <QMdiArea>

#include "ui_rendertiger.h"
#include "dx11_preview_window.h"
#include "dx11_fx_editor_window.h"
#include "lua_editor_window.h"

#include <xnamath.h>
#include "d3dx11effect.h"
#include "dx11_utils.h"

class render_tiger_main_window : public QMainWindow {
    Q_OBJECT
public:
    render_tiger_main_window(QWidget *parent = 0);
    ~render_tiger_main_window();
public:
    void on_preview_window_close();
    void on_fx_editor_close();
    void on_lua_editor_close();
private:
    void _init_events();
    void _init_lua();
private slots:
    void _on_action_preview(bool checked = false);
    void _on_action_shader_fx(bool checked = false);
    void _on_action_lua();
private:
    Ui::render_tiger_main_window_ui _ui;

    dx11_preview_window *_preview_window;
    dx11_fx_editor_window *_fx_editor;
    lua_editor_window *_lua_editor;
};

#endif
