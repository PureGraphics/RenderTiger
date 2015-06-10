#include "lua_editor_window.h"
#include "render_tiger_main_window.h"

lua_editor_window::lua_editor_window(QWidget *parent)
: QMainWindow(parent), _parent(parent),
_curr_text(""), _prev_text("") {
    _ui.setupUi(this);
    _init_keywords();
    _init_events();

    this->setMinimumSize(400, 400);
}

lua_editor_window::~lua_editor_window() {

}

void lua_editor_window::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);

    //TODO: How to do this correct? it looks like shit...
    render_tiger_main_window *main_wnd = (render_tiger_main_window*)_parent;
    main_wnd->on_lua_editor_close();
}

void lua_editor_window::_init_keywords() {
    _keywords.push_back("VF");
    //TODO...
}

void lua_editor_window::_init_events() {
    connect(_ui.text_editor->document(), &QTextDocument::contentsChanged, this, &lua_editor_window::_on_contents_changed);
}

void lua_editor_window::_on_contents_changed() {
    _prev_text = _curr_text;
    _prev_text = _prev_text.replace("\t", "    ");
    _curr_text = _ui.text_editor->document()->toPlainText();
    if (_prev_text == _curr_text || (_prev_text + "\n") == _curr_text) {
        return;
    }
    QString h_text = _curr_text;
    h_text = h_text.replace("\n", "<br/>");
    h_text = h_text.replace(" ", "&nbsp;");
    h_text = h_text.replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;");
    for (auto it = _keywords.begin(); it != _keywords.end(); ++it) {
        h_text = h_text.replace(*it, QString("<font color='#0000ff'>") + (*it) + QString("</font>"));
    }
    disconnect(_ui.text_editor->document(), &QTextDocument::contentsChanged, this, &lua_editor_window::_on_contents_changed);
    QTextCursor qtc = _ui.text_editor->textCursor();
    int p = qtc.position();
    _ui.text_editor->setHtml(h_text);
    qtc.setPosition(p);
    _ui.text_editor->setTextCursor(qtc);
    connect(_ui.text_editor->document(), &QTextDocument::contentsChanged, this, &lua_editor_window::_on_contents_changed);
}