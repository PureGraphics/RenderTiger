#include "dx11_vertex_buffer.h"

dx11_vertex_buffer::dx11_vertex_buffer() {
    
}

dx11_vertex_buffer::~dx11_vertex_buffer() {
    
}

void dx11_vertex_buffer::add_vb_element(float f) {
    _vb_element_list.push_back(f);
}

void dx11_vertex_buffer::add_ib_element(int i) {
    _ib_element_list.push_back(i);
}

void dx11_vertex_buffer::clear() {
    _vb_element_list.clear();
    _ib_element_list.clear();
}

const float * dx11_vertex_buffer::get_vb_pointer() const {
    return _vb_element_list.data();
}

const int * dx11_vertex_buffer::get_ib_pointer() const {
    return _ib_element_list.data();
}