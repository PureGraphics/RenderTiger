#ifndef dx11_preview_window_h
#define dx11_preview_window_h

#include <QMainWindow>

#include "qt5_dx11_app_framework.h"
#include "ui_dx11_preview_window.h"

#include <xnamath.h>
#include "d3dx11effect.h"
#include "dx11_utils.h"

class dx11_preview_window : public qt5_dx11_app_framework {
    Q_OBJECT
public:
    dx11_preview_window(QWidget *parent);
    ~dx11_preview_window();
public:
    bool init() override;
    void on_resize(QResizeEvent *event) override;
    void on_update() override;
    void on_draw() override;
    void on_keyborad(QKeyEvent *event) override;
    void on_mouse_press(QMouseEvent *event) override;
    void on_mouse_release(QMouseEvent *event) override;
    void on_mouse_move(QMouseEvent *event) override;
protected: //override Qt inner methods.
    void closeEvent(QCloseEvent *event) override;
private:
    void build_vertex_buffer();
    void build_fx();
    void build_vertex_layout();
private:
    Ui::dx11_preview_window _ui;
    QWidget *_parent;
private:
    ID3D11Buffer *_box_vb;
    ID3D11Buffer *_box_ib;
    ID3DX11Effect *_fx;
    ID3DX11EffectTechnique *_tech;
    ID3DX11EffectMatrixVariable *_mat_wvp;
    ID3D11InputLayout *_input_layout;

    XMFLOAT4X4 _mat_world;
    XMFLOAT4X4 _mat_view;
    XMFLOAT4X4 _mat_proj;

    float _theta;
    float _phi;
    float _radius;
    POINT _last_mouse_pos;
    Qt::MouseButton _mouse_btn_when_pressed;
};

#endif