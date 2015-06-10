#ifndef qt5_dx11_app_framework_h
#define qt5_dx11_app_framework_h

#include <QMainWindow>
#include <QTimer>
#include <QMdiSubWindow>

#include <d3d11.h>

#include "timer.h"

class qt5_dx11_app_framework : public QMainWindow {
    Q_OBJECT
public:
    qt5_dx11_app_framework(QWidget *parent = 0);
    virtual ~qt5_dx11_app_framework();
public:
    void set_fps(unsigned int fps);
    WId  get_win_id() const;
    HWND get_win_hwnd() const;
    float get_aspect_radio() const;
    void run();
public:
    virtual bool init(const float *vb_data, int vb_sz, const int *ib_data, int ib_sz);
    virtual void on_resize(QResizeEvent *event);
    virtual void on_update();
    virtual void on_draw();
    virtual void on_keyborad(QKeyEvent *event);
    virtual void on_mouse_press(QMouseEvent *event);
    virtual void on_mouse_release(QMouseEvent *event);
    virtual void on_mouse_move(QMouseEvent *event);
public slots:
    void run_on_timer();
protected: //Qt5 inner methods.
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
private:
    void _set_win_id(WId wid);
    bool _init_dx11();
    void _calculate_frame_stats();
protected:
    ID3D11Device *_device;
    ID3D11DeviceContext *_context;
    IDXGISwapChain *_swap_chain;
    ID3D11Texture2D *_depth_stencil_buffer;
    ID3D11DepthStencilView *_depth_stencil_view;
    ID3D11RenderTargetView *_render_target_view;
    D3D11_VIEWPORT _viewport;
    D3D_DRIVER_TYPE _drive_type;

    int _client_w;
    int _client_h;
    bool _enable_4xmsaa;
    unsigned int _msaa_quality_level;
private:
    WId  _wid;
    HWND _hwnd;
    timer _timer;
    QTimer *_qtimer;
    unsigned int _fps;
};

#endif