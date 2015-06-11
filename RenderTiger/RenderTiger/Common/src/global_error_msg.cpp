#include "global_error_msg.h"

#include <assert.h>

global_error_msg * global_error_msg::get_instance() {
    static global_error_msg * inst = nullptr;
    if (inst == nullptr)
        inst = new global_error_msg();
    return inst;
}

global_error_msg::global_error_msg() 
:_target(nullptr) {
    
}

global_error_msg::~global_error_msg() {
    
}

void global_error_msg::set_output_target(QTextEdit *target) {
    _target = target;
}

void global_error_msg::add_error_msg(QString msg) {
    _error_msg_list.push_back(msg);
    assert(_target != nullptr);
    _target->append(msg);
}

void global_error_msg::clear() {
    _error_msg_list.clear();
}

int global_error_msg::len() const {
    return _error_msg_list.size();
}

QString global_error_msg::operator[](uint i) {
    assert(i < _error_msg_list.size());
    return _error_msg_list[i];
}