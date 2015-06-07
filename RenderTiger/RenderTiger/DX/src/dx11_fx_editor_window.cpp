#include "dx11_fx_editor_window.h"
#include "render_tiger_main_window.h"

dx11_fx_editor_window::dx11_fx_editor_window(QWidget *parent)
: QMainWindow(parent), _parent(parent) {
    _ui.setupUi(this);
}

dx11_fx_editor_window::~dx11_fx_editor_window() {

}

void dx11_fx_editor_window::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);

    //How to do this correct? it looks like shit...
    render_tiger_main_window *main_wnd = (render_tiger_main_window*)_parent;
    main_wnd->on_fx_editor_close();
}
