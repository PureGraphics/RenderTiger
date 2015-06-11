#ifndef global_msg_h
#define global_msg_h

#include <QList>
#include <QString>
#include <QTextEdit>

class msg_node {
public:
    msg_node(QString msg, int line_num);
    ~msg_node();
public:
    QString msg;
    int line_num;
};

class global_msg {
public:
    static global_msg * get_instance();
private:
    global_msg();
    ~global_msg();
public:
    void set_output_target(QTextEdit *target);
    void add_error_msg(QString msg);
    void add_info_msg(QString msg);
    bool has_error_msg() const;
    void clear();
private:
    QList<QString> _error_msg_list;
    QList<QString> _info_msg_list;
    QTextEdit *_target;
};

#endif