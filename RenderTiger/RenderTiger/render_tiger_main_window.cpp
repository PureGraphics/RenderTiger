#include "render_tiger_main_window.h"

#include <assert.h>
#include <QMouseEvent>

render_tiger_main_window::render_tiger_main_window(QWidget *parent)
: QMainWindow(parent),
_preview_window(nullptr) {
    _ui.setupUi(this);
    _init_events();
}

render_tiger_main_window::~render_tiger_main_window() {
    
}

void render_tiger_main_window::_init_events() {
    //connect(_ui.actionPreview, SIGNAL(QAction::activate()), this, SLOT(render_tiger_main_window::_on_action_preview()));
    connect(_ui.actionPreview, &QAction::triggered, this, &render_tiger_main_window::_on_action_preview);
}

void render_tiger_main_window::_on_action_preview(bool checked) {
    int d = 0;
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

void render_tiger_main_window::on_preview_window_close() {
    if (_preview_window != nullptr)
        delete _preview_window;
    _preview_window = nullptr;

    _ui.actionPreview->setChecked(false);
}