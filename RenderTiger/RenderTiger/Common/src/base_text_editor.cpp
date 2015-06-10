#include "base_text_editor.h"

#include <assert.h>
#include <QChar>

base_text_editor::base_text_editor() {
    
}

base_text_editor::~base_text_editor() {
    
}

void base_text_editor::_init_keywords() {
    assert(false);
}

QString base_text_editor::_highlight_keywords(QString src, int &tab) {
    QList<QString> tokens;
    bool in_word = false;
    QString word = "";
    for (int i = 0; i < src.size(); i++) {
        QChar c = src[i];
        if (c.isLetter() || c.isDigit() || c == '_') {
            in_word = true;
            word += c;
        } else {
            if (in_word) {
                in_word = false;
                tokens.push_back(word);
                word.clear();
            }
            tokens.push_back(c);
        }
    }
    if (!word.isEmpty())
        tokens.push_back(word);

    QString ret = "";
    tab = 0;
    for (int i = 0; i < tokens.size(); i++) {
        QString token = tokens[i];
        if (token == " ")
            ret += "&nbsp;";
        else if (token == "\n")
            ret += "<br/>";
        else if (token == "\t") {
            ret += "&nbsp;&nbsp;&nbsp;&nbsp;";
            tab += 3;
        }
        else if (token == "<")
            ret += "&lt;";
        else if (_is_keyword(token))
            ret += "<font color='#0000ff'>" + token + "</font>";
        else
            ret += token;
    }

    return ret;
}

bool base_text_editor::_is_keyword(const QString &token) {
    return _keywords.contains(token);
}