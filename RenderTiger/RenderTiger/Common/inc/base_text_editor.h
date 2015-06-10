#ifndef base_text_editor_h
#define base_text_editor_h

#include <QString>
#include <QList>

class base_text_editor {
public:
    base_text_editor();
    virtual ~base_text_editor();
protected:
    virtual void _init_keywords();
    QString _highlight_keywords(QString src, int &tab);
private:
    bool _is_keyword(const QString &token);
protected:
    QList<QString> _keywords;
};

#endif