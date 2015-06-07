#include "render_tiger_main_window.h"

#include <assert.h>
#include <QMouseEvent>

render_tiger_main_window::render_tiger_main_window(QWidget *parent)
: QMainWindow(parent),
_preview_window(nullptr),
_fx_editor(nullptr) {
    _ui.setupUi(this);
    _init_events();
}

render_tiger_main_window::~render_tiger_main_window() {
    
}

void render_tiger_main_window::_init_events() {
    //connect(_ui.actionPreview, SIGNAL(QAction::activate()), this, SLOT(render_tiger_main_window::_on_action_preview()));
    connect(_ui.actionPreview, &QAction::triggered, this, &render_tiger_main_window::_on_action_preview);
    connect(_ui.actionShader_fx, &QAction::triggered, this, &render_tiger_main_window::_on_action_shader_fx);
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