#include "render_tiger_main_window.h"

#include <assert.h>

#include <QMouseEvent>
#include <QMessageBox>

#include "lua.hpp"

#include "lua_global_error_msg.h"
#include "lua_dx11_vertex_buffer.h"

lua_State *g_lua_state = nullptr;

render_tiger_main_window::render_tiger_main_window(QWidget *parent)
: QMainWindow(parent),
_preview_window(nullptr),
_fx_editor(nullptr),
_lua_editor(nullptr) {
    _ui.setupUi(this);
    _init_events();
    _init_lua();
}

render_tiger_main_window::~render_tiger_main_window() {
    
}

void render_tiger_main_window::_init_events() {
    //connect(_ui.actionPreview, SIGNAL(QAction::activate()), this, SLOT(render_tiger_main_window::_on_action_preview()));
    connect(_ui.actionPreview, &QAction::triggered, this, &render_tiger_main_window::_on_action_preview);
    connect(_ui.actionShader_fx, &QAction::triggered, this, &render_tiger_main_window::_on_action_shader_fx);
    connect(_ui.actionLua, &QAction::triggered, this, &render_tiger_main_window::_on_action_lua);
    connect(_ui.actionCompile, &QAction::triggered, this, &render_tiger_main_window::_on_action_compile);
}

void render_tiger_main_window::_init_lua() {
    g_lua_state = luaL_newstate();
    luaL_openlibs(g_lua_state);

    luaL_requiref(g_lua_state, "rendertiger.error_msg", lua_global_error_msg, 0);
    luaL_requiref(g_lua_state, "rendertiger.vertex_buffer", lua_dx11_vertex_buffer, 0);
}

void render_tiger_main_window::_on_action_preview(bool checked) {
    if (_ui.actionPreview->isChecked()) {
        if (_preview_window == nullptr) {
            _preview_window = new dx11_preview_window(this);
            _ui.mdiArea->addSubWindow(_preview_window);
        }
        _preview_window->showNormal();
    }
    else {
        if (_preview_window) {
            _preview_window->showMinimized();
        }
    }
}

void render_tiger_main_window::_on_action_shader_fx(bool checked) {
    if (_ui.actionShader_fx->isChecked()) {
        if (_fx_editor == nullptr) {
            _fx_editor = new dx11_fx_editor_window(this);
            _ui.mdiArea->addSubWindow(_fx_editor);
        }
        _fx_editor->showNormal();
    }
    else {
        if (_fx_editor) {
            _fx_editor->showMinimized();
        }
    }
}

void render_tiger_main_window::_on_action_lua() {
    if (_ui.actionLua->isChecked()) {
        if (_lua_editor == nullptr) {
            _lua_editor = new lua_editor_window(this);
            _ui.mdiArea->addSubWindow(_lua_editor);
        }
        _lua_editor->showNormal();
    }
    else {
        if (_lua_editor) {
            _lua_editor->showMinimized();
        }
    }
}

void render_tiger_main_window::_on_action_compile() {
    if (_lua_editor == nullptr)
        return;
    QString lua_src = _lua_editor->get_lua_src();
    if (lua_src.isEmpty()) {
        QMessageBox::information(NULL, "", "I need lua code.", QMessageBox::Ok);
        return;
    }
    //test.
    int err = luaL_dostring(g_lua_state, lua_src.toStdString().c_str());
    if (err) {
        const char *msg = lua_tostring(g_lua_state, -1);
        QMessageBox::information(NULL, "lua error", msg, QMessageBox::Ok);
        return;
    }
}

void render_tiger_main_window::on_preview_window_close() {
    if (_preview_window != nullptr)
        delete _preview_window;
    _preview_window = nullptr;

    _ui.actionPreview->setChecked(false);
}

void render_tiger_main_window::on_fx_editor_close() {
    if (_fx_editor != nullptr)
        delete _fx_editor;
    _fx_editor = nullptr;

    _ui.actionShader_fx->setChecked(false);
}

void render_tiger_main_window::on_lua_editor_close() {
    if (_lua_editor != nullptr)
        delete _lua_editor;
    _lua_editor = nullptr;

    _ui.actionLua->setChecked(false);
}