#ifndef RENDERTIGER_H
#define RENDERTIGER_H

#include <QtWidgets/QMainWindow>
#include "ui_rendertiger.h"

#include "qt5_dx11_app_framework.h"

#include <d3d11.h>
#include <xnamath.h>
#include "d3dx11effect.h"
#include "dx11_utils.h"

class cube : public qt5_dx11_app_framework {
public:
    cube(QMainWindow *target);
    ~cube();
public:
    bool init() override;
    void on_resize() override;
    void on_update() override;
    void on_draw() override;
    void on_mouse() override;
    void on_keyborad() override;
private:
    void build_vertex_buffer();
    void build_fx();
    void build_vertex_layout();
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
};

class render_triger_main_window : public QMainWindow {
    Q_OBJECT
public:
    render_triger_main_window(QWidget *parent = 0);
    ~render_triger_main_window();
public slots:
    void slot_on_timer();
private:
    Ui::RenderTigerClass ui;
    cube *_cube;
};

#endif
