#include "dx11_fx_editor_window.h"
#include "render_tiger_main_window.h"

dx11_fx_editor_window::dx11_fx_editor_window(QWidget *parent)
: QMainWindow(parent), _parent(parent),
_curr_text(""), _prev_text("") {
    _ui.setupUi(this);
    _init_keywords();
    _init_events();

    this->setMinimumSize(400, 400);
}

dx11_fx_editor_window::~dx11_fx_editor_window() {
    
}

void dx11_fx_editor_window::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);

    //How to do this correct? it looks like shit...
    render_tiger_main_window *main_wnd = (render_tiger_main_window*)_parent;
    main_wnd->on_fx_editor_close();
}

void dx11_fx_editor_window::_init_keywords() {
    _keywords.push_back("matrix4x4");
    _keywords.push_back("float4x4");
    _keywords.push_back("float2");
    _keywords.push_back("float3");
    _keywords.push_back("float4");
    _keywords.push_back("int");
    _keywords.push_back("float");
    _keywords.push_back("half");
    _keywords.push_back("double");
    _keywords.push_back("vector");
    _keywords.push_back("matrix");
    _keywords.push_back("texture");
    _keywords.push_back("struct");
    _keywords.push_back("cbuffer");
    _keywords.push_back("POSITION");
    _keywords.push_back("COLOR");
    _keywords.push_back("SV_POSITION");
    _keywords.push_back("return");
    _keywords.push_back("mul");
    _keywords.push_back("pass");
    _keywords.push_back("SetVertexShader");
    _keywords.push_back("SetGeometryShader");
    _keywords.push_back("SetPixelShader");
    _keywords.push_back("NULL");
}

void dx11_fx_editor_window::_init_events() {
    connect(_ui.text_editor->document(), &QTextDocument::contentsChanged, this, &dx11_fx_editor_window::_on_contents_changed);
}

void dx11_fx_editor_window::_on_contents_changed() {
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
    disconnect(_ui.text_editor->document(), &QTextDocument::contentsChanged, this, &dx11_fx_editor_window::_on_contents_changed);
    QTextCursor qtc = _ui.text_editor->textCursor();
    int p = qtc.position();
    _ui.text_editor->setHtml(h_text);
    qtc.setPosition(p);
    _ui.text_editor->setTextCursor(qtc);
    connect(_ui.text_editor->document(), &QTextDocument::contentsChanged, this, &dx11_fx_editor_window::_on_contents_changed);
}