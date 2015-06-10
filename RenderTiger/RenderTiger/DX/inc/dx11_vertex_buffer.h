#ifndef dx11_vertex_buffer_h
#define dx11_vertex_buffer_h

#include <QVector>
#include <QString>

class dx11_vertex_buffer {
public:
    dx11_vertex_buffer();
    ~dx11_vertex_buffer();
public:
    void add_vb_element(float f);
    void add_ib_element(int i);
    void add_input_layout(QString layout);
    void clear();
    const float * get_vb_pointer() const;
    int get_vb_byte_size() const;
    const int * get_ib_pointer() const;
    int get_ib_byte_size() const;
private:
    QVector<float> _vb_element_list;
    QVector<int> _ib_element_list;
    QVector<QString> _layout_list;
};

#endif