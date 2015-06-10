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

QString lua_editor_window::get_lua_src() {
    return _ui.text_editor->toPlainText();
}

void lua_editor_window::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);

    //TODO: How to do this correct? it looks like shit...
    render_tiger_main_window *main_wnd = (render_tiger_main_window*)_parent;
    main_wnd->on_lua_editor_close();
}

void lua_editor_window::_init_keywords() {
    _keywords.push_back("and");
    _keywords.push_back("break");
    _keywords.push_back("do");
    _keywords.push_back("else");
    _keywords.push_back("elseif");
    _keywords.push_back("end");
    _keywords.push_back("false");
    _keywords.push_back("for");
    _keywords.push_back("function");
    _keywords.push_back("goto");
    _keywords.push_back("if");
    _keywords.push_back("in");
    _keywords.push_back("local");
    _keywords.push_back("nil");
    _keywords.push_back("not");
    _keywords.push_back("or");
    _keywords.push_back("repeat");
    _keywords.push_back("return");
    _keywords.push_back("then");
    _keywords.push_back("true");
    _keywords.push_back("until");
    _keywords.push_back("while");

    _keywords.push_back("VF");
    _keywords.push_back("_G");
    _keywords.push_back("io");
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
    h_text = " " + h_text + " ";
    h_text = h_text.replace("\n", "<br/>");
    h_text = h_text.replace(" ", "&nbsp;");
    h_text = h_text.replace("\t", "&nbsp;&nbsp;&nbsp;&nbsp;");
    for (auto it = _keywords.begin(); it != _keywords.end(); ++it) {
        QString k = "&nbsp;" + (*it) + "&nbsp;";
        h_text = h_text.replace(k, QString("&nbsp;<font color='#0000ff'>") + (*it) + QString("</font>&nbsp;"));
    }
    h_text = h_text.remove(0, 6);
    h_text = h_text.remove(h_text.size() - 6, 6);
    disconnect(_ui.text_editor->document(), &QTextDocument::contentsChanged, this, &lua_editor_window::_on_contents_changed);
    QTextCursor qtc = _ui.text_editor->textCursor();
    int p = qtc.position();
    _ui.text_editor->setHtml(h_text);
    qtc.setPosition(p);
    _ui.text_editor->setTextCursor(qtc);
    connect(_ui.text_editor->document(), &QTextDocument::contentsChanged, this, &lua_editor_window::_on_contents_changed);
}