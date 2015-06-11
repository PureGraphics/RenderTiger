#include "render_tiger_main_window.h"

#include <assert.h>

#include <QMouseEvent>
#include <QMessageBox>
#include <QTextEdit>

#include "lua.hpp"

#include "lua_global_msg.h"
#include "lua_dx11_vertex_buffer.h"
#include "dx11_vertex_buffer.h"
#include "global_msg.h"

lua_State *g_lua_state = nullptr;

//for quick test.
extern dx11_vertex_buffer *g_test_dx11_vb;
//end test.

render_tiger_main_window::render_tiger_main_window(QWidget *parent)
: QMainWindow(parent),
_preview_window(nullptr),
_fx_editor(nullptr),
_lua_editor(nullptr) {
    _ui.setupUi(this);
    _init_events();
    _init_lua();
    global_msg::get_instance()->set_output_target(_ui.output_textEdit);
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

    luaL_requiref(g_lua_state, "rendertiger.msg", lua_global_msg, 0);
    luaL_requiref(g_lua_state, "rendertiger.vertex_buffer", lua_dx11_vertex_buffer, 0);
}

void render_tiger_main_window::_compile_and_preview() {
    if (_preview_window == nullptr) {
        _preview_window = new dx11_preview_window(this);
        _ui.mdiArea->addSubWindow(_preview_window);
    }
    const float *vb_data = g_test_dx11_vb->get_vb_pointer();
    int vb_sz = g_test_dx11_vb->get_vb_byte_size();
    const int *ib_data = g_test_dx11_vb->get_ib_pointer();
    int ib_sz = g_test_dx11_vb->get_ib_byte_size();
    _preview_window->init(vb_data, vb_sz, ib_data, ib_sz);
    _preview_window->showNormal();
    _ui.actionPreview->setChecked(true);
}

void render_tiger_main_window::_on_action_preview(bool checked) {
    if (_ui.actionPreview->isChecked()) {
        if (_preview_window == nullptr) {
            _preview_window = new dx11_preview_window(this);
            const float *vb_data = g_test_dx11_vb->get_vb_pointer();
            int vb_sz = g_test_dx11_vb->get_vb_byte_size();
            const int *ib_data = g_test_dx11_vb->get_ib_pointer();
            int ib_sz = g_test_dx11_vb->get_ib_byte_size();
            _preview_window->init(vb_data, vb_sz, ib_data, ib_sz);
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
    global_msg::get_instance()->clear();
    if (g_test_dx11_vb)
        g_test_dx11_vb->clear();
    _ui.output_textEdit->clear();

    if (_lua_editor == nullptr)
        return;
    QString lua_src = _lua_editor->get_lua_src();
    if (lua_src.isEmpty()) {
        global_msg::get_instance()->add_error_msg("I need lua code.");
        return;
    }
    lua_settop(g_lua_state, 0);
    int err = luaL_loadfile(g_lua_state, "Lua/render_tiger_exchanger.lua");
    if (err) {
        const char *msg = lua_tostring(g_lua_state, -1);
        global_msg::get_instance()->add_error_msg(QString("render_tiger_exchanger::") + msg);
        return;
    }
    lua_pushstring(g_lua_state, _lua_editor->get_lua_src().toStdString().c_str());
    err = lua_pcall(g_lua_state, 1, 0, NULL);
    if (err) {
        const char *msg = lua_tostring(g_lua_state, -1);
        global_msg::get_instance()->add_error_msg(msg);
        return;
    }

    if (!global_msg::get_instance()->has_error_msg()) {
        global_msg::get_instance()->add_info_msg("Lua compile success");
        _compile_and_preview();
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