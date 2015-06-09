#include "global_error_msg.h"

global_error_msg * global_error_msg::get_instance() {
    static global_error_msg * inst = nullptr;
    if (inst == nullptr)
        inst = new global_error_msg();
    return inst;
}

global_error_msg::global_error_msg() {
    
}

global_error_msg::~global_error_msg() {
    
}

void global_error_msg::add_error_msg(QString msg) {
    _error_msg_list.push_back(msg);
}

void global_error_msg::clear() {
    _error_msg_list.clear();
}