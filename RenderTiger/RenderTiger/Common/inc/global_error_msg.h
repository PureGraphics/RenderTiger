#ifndef global_error_msg_h
#define global_error_msg_h

#include <QList>
#include <QString>

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
    void add_error_msg(QString msg);
    void clear();
private:
    QList<QString> _error_msg_list;
};

#endif