#include "global_msg.h"

#include <assert.h>

global_msg * global_msg::get_instance() {
    static global_msg * inst = nullptr;
    if (inst == nullptr)
        inst = new global_msg();
    return inst;
}

global_msg::global_msg() 
:_target(nullptr) {
    
}

global_msg::~global_msg() {
    
}

void global_msg::set_output_target(QTextEdit *target) {
    _target = target;
}

void global_msg::add_error_msg(QString msg) {
    _error_msg_list.push_back(msg);
    assert(_target != nullptr);
    _target->append("[ERROR] " + msg);
}

void global_msg::add_info_msg(QString msg) {
    _info_msg_list.push_back(msg);
    assert(_target != nullptr);
    _target->append("[INFO] " + msg);
}

bool global_msg::has_error_msg() const {
    return _error_msg_list.size() > 0;
}

void global_msg::clear() {
    _error_msg_list.clear();
    _info_msg_list.clear();
}