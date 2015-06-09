#ifndef dx11_vertex_buffer_h
#define dx11_vertex_buffer_h

#include <QVector>

class dx11_vertex_buffer {
public:
    dx11_vertex_buffer();
    ~dx11_vertex_buffer();
public:
    void add_vb_element(float f);
    void add_ib_element(int i);
    void clear();
    const float * get_vb_pointer() const;
    const int * get_ib_pointer() const;
private:
    QVector<float> _vb_element_list;
    QVector<int> _ib_element_list;
};

#endif