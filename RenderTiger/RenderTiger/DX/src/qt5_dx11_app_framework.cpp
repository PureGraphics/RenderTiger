#include "qt5_dx11_app_framework.h"
#include "dx11_utils.h"

#include <assert.h>
#include <string>
#include <sstream>

#include <QGroupBox>

qt5_dx11_app_framework::qt5_dx11_app_framework(QMainWindow *target)
:
_target_qmain_window(target),
_fps(60),
_qtimer(nullptr),
_device(nullptr),
_context(nullptr),
_swap_chain(nullptr),
_depth_stencil_buffer(nullptr),
_depth_stencil_view(nullptr),
_render_target_view(nullptr),
_drive_type(D3D_DRIVER_TYPE_HARDWARE),
_enable_4xmsaa(false) {
    _timer.start();
    _client_w = target->width();
    _client_h = target->height();
    _set_win_id(target->winId());
    ZeroMemory(&_viewport, sizeof(_viewport));
}

qt5_dx11_app_framework::~qt5_dx11_app_framework() {
    safe_release(_device);
    safe_release(_swap_chain);
    safe_release(_depth_stencil_buffer);
    safe_release(_depth_stencil_view);
    safe_release(_render_target_view);

    if (_context != nullptr) {
        _context->ClearState();
    }
    safe_release(_context);
}

void qt5_dx11_app_framework::set_fps(unsigned int fps) {
    _fps = fps;
}

WId qt5_dx11_app_framework::get_win_id() const {
    return _wid;
}

HWND qt5_dx11_app_framework::get_win_hwnd() const {
    return _hwnd;
}

float qt5_dx11_app_framework::get_aspect_radio() const {
    return (float)_client_w / _client_h;
}

void qt5_dx11_app_framework::run() {
    if (_qtimer != nullptr) {
        if (_qtimer->isActive())
            _qtimer->stop();
    }
    else {
        _qtimer = new QTimer(_target_qmain_window);
    }
    QObject::connect(_qtimer, SIGNAL(timeout()), _target_qmain_window, SLOT(slot_on_timer()));
    _qtimer->start(1000.0f / _fps);
}

bool qt5_dx11_app_framework::init() {
    if (!_init_dx11())
        return false;
    return true;
}

void qt5_dx11_app_framework::on_resize() {
    assert(_context);
    assert(_device);
    assert(_swap_chain);

    safe_release(_render_target_view);
    safe_release(_depth_stencil_view);
    safe_release(_depth_stencil_buffer);

    HR(_swap_chain->ResizeBuffers(1, _client_w, _client_h, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
    ID3D11Texture2D *back_buffer;
    HR(_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer)));
    HR(_device->CreateRenderTargetView(back_buffer, 0, &_render_target_view));
    safe_release(back_buffer);

    D3D11_TEXTURE2D_DESC ds_desc;
    ds_desc.Width = _client_w;
    ds_desc.Height = _client_h;
    ds_desc.MipLevels = 1;
    ds_desc.ArraySize = 1;
    ds_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

    if (_enable_4xmsaa) {
        ds_desc.SampleDesc.Count = 4;
        ds_desc.SampleDesc.Quality = _msaa_quality_level - 1;
    }
    else {
        ds_desc.SampleDesc.Count = 1;
        ds_desc.SampleDesc.Quality = 0;
    }

    ds_desc.Usage = D3D11_USAGE_DEFAULT;
    ds_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    ds_desc.CPUAccessFlags = 0;
    ds_desc.MiscFlags = 0;

    HR(_device->CreateTexture2D(&ds_desc, 0, &_depth_stencil_buffer));
    HR(_device->CreateDepthStencilView(_depth_stencil_buffer, 0, &_depth_stencil_view));

    _context->OMSetRenderTargets(1, &_render_target_view, _depth_stencil_view);

    _viewport.TopLeftX = 0;
    _viewport.TopLeftY = 0;
    _viewport.Width = static_cast<float>(_client_w);
    _viewport.Height = static_cast<float>(_client_h);
    _viewport.MinDepth = 0.0f;
    _viewport.MaxDepth = 1.0f;

    _context->RSSetViewports(1, &_viewport);
}

void qt5_dx11_app_framework::on_update() {

}

void qt5_dx11_app_framework::on_draw() {

}

void qt5_dx11_app_framework::on_mouse() {

}

void qt5_dx11_app_framework::on_keyborad() {

}

void qt5_dx11_app_framework::_set_win_id(WId wid) {
    _wid = wid;
    _hwnd = (HWND)wid;
}

void qt5_dx11_app_framework::_run_on_timer() {
    _calculate_frame_stats();
    on_update();
    on_draw();
}

bool qt5_dx11_app_framework::_init_dx11() {
    //Create the device and device context.
    UINT create_device_flags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL feature_level;
    HRESULT hr = D3D11CreateDevice (
        0,
        _drive_type,
        0,
        create_device_flags,
        0, 0,
        D3D11_SDK_VERSION,
        &_device,
        &feature_level,
        &_context);
    if (FAILED(hr)) {
        MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
        return false;
    }
    if (feature_level != D3D_FEATURE_LEVEL_11_0) {
        MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
        return false;
    }
    UINT msaa_quality_level;
    HR(_device->CheckMultisampleQualityLevels(
        DXGI_FORMAT_R8G8B8A8_UNORM, 4, &_msaa_quality_level));
    assert(_msaa_quality_level > 0);

    //Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap-chain.
    DXGI_SWAP_CHAIN_DESC sd;
    sd.BufferDesc.Width = _client_w;
    sd.BufferDesc.Height = _client_h;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    if (_enable_4xmsaa) {
        sd.SampleDesc.Count = 4;
        sd.SampleDesc.Quality = _msaa_quality_level - 1;
    }
    else {
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
    }

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 1;
    sd.OutputWindow = _hwnd;
    sd.Windowed = true;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = 0;

    // To correctly create the swap chain, we must use the IDXGIFactory that was
    // used to create the device.  If we tried to use a different IDXGIFactory instance
    // (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
    // This function is being called with a device from a different IDXGIFactory."

    IDXGIDevice *dxgi_device = 0;
    HR(_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi_device));

    IDXGIAdapter *dxgi_adapter = 0;
    HR(dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgi_adapter));

    IDXGIFactory *dxgi_factory = 0;
    HR(dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgi_factory));

    HR(dxgi_factory->CreateSwapChain(_device, &sd, &_swap_chain));

    safe_release(dxgi_device);
    safe_release(dxgi_adapter);
    safe_release(dxgi_factory);

    on_resize();

    return true;
}

void qt5_dx11_app_framework::_calculate_frame_stats() {
    static int frame_count = 0;
    static float time_elapsed = 0.0f;

    frame_count++;

    //Compute averages over one second period.
    if (_timer.get_time_since_start() - time_elapsed >= 1.0f) {
        float fps = (float)frame_count;
        float mspf = 1000.0f / fps;

        //TODO: Frame Stats form.

        //Reset for next average.
        frame_count = 0;
        time_elapsed += 1.0f;
    }
}