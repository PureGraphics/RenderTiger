#ifndef global_error_msg_h
#define global_error_msg_h

#include <QList>
#include <QString>
#include <QTextEdit>

class error_msg_node {
public:
    error_msg_node(QString err_msg, int err_line_num);
    ~error_msg_node();
public:
    QString msg;
    int line_num;
};

class global_error_msg {
public:
    static global_error_msg * get_instance();
private:
    global_error_msg();
    ~global_error_msg();
public:
    void set_output_target(QTextEdit *target);
    void add_error_msg(QString msg);
    void clear();
    int len() const;
    QString operator[](uint i);
private:
    QList<QString> _error_msg_list;
    QTextEdit *_target;
};

#endif