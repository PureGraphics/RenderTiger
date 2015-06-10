#include "dx11_preview_window.h"

#include "render_tiger_main_window.h"

#include <assert.h>
#include <QMouseEvent>

dx11_preview_window::dx11_preview_window(QWidget *parent)
: qt5_dx11_app_framework(parent), _parent(parent),
_geometry_vb(0), _geomery_ib(0), _fx(0), _tech(0),
_mat_wvp(0), _input_layout(0),
_theta(1.5f * XM_PI), _phi(0.25f * XM_PI), _radius(5.0f) {
    _ui.setupUi(this);

    XMMATRIX I = XMMatrixIdentity();
    XMStoreFloat4x4(&_mat_world, I);
    XMStoreFloat4x4(&_mat_view, I);
    XMStoreFloat4x4(&_mat_proj, I);

    setMinimumSize(400, 400);
}

dx11_preview_window::~dx11_preview_window() {
    safe_release(_geometry_vb);
    safe_release(_geomery_ib);
    safe_release(_fx);
    safe_release(_input_layout);
}

bool dx11_preview_window::init(const float *vb_data, int vb_sz, const int *ib_data, int ib_sz) {
    if (!qt5_dx11_app_framework::init(vb_data, vb_sz, ib_data, ib_sz))
        return false;

    _build_vertex_buffer(vb_data, vb_sz, ib_data, ib_sz);
    _build_fx();
    _build_vertex_layout();

    run();
    return true;
}

void dx11_preview_window::on_resize(QResizeEvent *event) {
    qt5_dx11_app_framework::on_resize(event);

    //The windows resized, so update the aspect ratio and recomputed the projection matrix.
    XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * XM_PI, get_aspect_radio(), 1.0f, 1000.0f);
    XMStoreFloat4x4(&_mat_proj, P);
}

void dx11_preview_window::on_update() {
    //Convert Spherical to Cartesian coordinates.
    float x = _radius * sinf(_phi) * cosf(_theta);
    float z = _radius * sinf(_phi) * sinf(_theta);
    float y = _radius * cosf(_phi);

    XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
    XMStoreFloat4x4(&_mat_view, V);
}

void dx11_preview_window::on_draw() {
    _context->ClearRenderTargetView(_render_target_view, reinterpret_cast<const float*>(&Colors::Black));
    _context->ClearDepthStencilView(_depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    _context->IASetInputLayout(_input_layout);
    _context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    UINT stride = 24; //TODO: hard code for a quick test.
    UINT offset = 0;
    _context->IASetVertexBuffers(0, 1, &_geometry_vb, &stride, &offset);
    _context->IASetIndexBuffer(_geomery_ib, DXGI_FORMAT_R32_UINT, 0);

    XMMATRIX world = XMLoadFloat4x4(&_mat_world);
    XMMATRIX view = XMLoadFloat4x4(&_mat_view);
    XMMATRIX proj = XMLoadFloat4x4(&_mat_proj);
    XMMATRIX mat_wvp = world * view * proj;

    _mat_wvp->SetMatrix(reinterpret_cast<float*>(&mat_wvp));

    D3DX11_TECHNIQUE_DESC tech_desc;
    _tech->GetDesc(&tech_desc);
    for (UINT p = 0; p < tech_desc.Passes; p++) {
        _tech->GetPassByIndex(p)->Apply(0, _context);
        _context->DrawIndexed(3, 0, 0);
    }

    HR(_swap_chain->Present(0, 0));
}

void dx11_preview_window::on_keyborad(QKeyEvent *event) {

}

void dx11_preview_window::on_mouse_press(QMouseEvent *event) {
    _last_mouse_pos.x = event->x();
    _last_mouse_pos.y = event->y();
    _mouse_btn_when_pressed = event->button();
    SetCapture(get_win_hwnd());
}

void dx11_preview_window::on_mouse_release(QMouseEvent *event) {
    ReleaseCapture();
}

template<typename T>
static T _clamp(const T& x, const T& low, const T& high) {
    return x < low ? low : (x > high ? high : x);
}

void dx11_preview_window::on_mouse_move(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    if (_mouse_btn_when_pressed == Qt::LeftButton) {
        float dx = XMConvertToRadians(0.25f * (float)(x - _last_mouse_pos.x));
        float dy = XMConvertToRadians(0.25f * (float)(y - _last_mouse_pos.y));
        _theta += dx;
        _phi += dy;

        _phi = _clamp(_phi, 0.1f, XM_PI - 0.1f);
    }
    else if (_mouse_btn_when_pressed == Qt::RightButton) {
        float dx = 0.005f * static_cast<float>(x - _last_mouse_pos.x);
        float dy = 0.005f * static_cast<float>(y - _last_mouse_pos.y);
        _radius += dx - dy;
        _radius = _clamp(_radius, 3.0f, 15.0f);
    }

    _last_mouse_pos.x = x;
    _last_mouse_pos.y = y;
}

void dx11_preview_window::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);
    //How to do this correct? it looks like shit...
    render_tiger_main_window *main_wnd = (render_tiger_main_window*)_parent;
    main_wnd->on_preview_window_close();
}

void dx11_preview_window::_build_vertex_buffer(const float *vb_data, int vb_sz, const int *ib_data, int ib_sz) {
    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = 24 * 3;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    vbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = vb_data;
    HR(_device->CreateBuffer(&vbd, &vinitData, &_geometry_vb));

    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = sizeof(UINT)* 3;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    ibd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = ib_data;
    HR(_device->CreateBuffer(&ibd, &iinitData, &_geomery_ib));
}

void dx11_preview_window::_build_fx() {
    DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    shaderFlags |= D3D10_SHADER_DEBUG;
    shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

    ID3D10Blob *compiled_shader = 0;
    ID3D10Blob *compilation_msgs = 0;
    HRESULT hr = D3DX11CompileFromFile(L"TestFX/test.fx", 0, 0, 0, "fx_5_0", shaderFlags,
        0, 0, &compiled_shader, &compilation_msgs, 0);
    if (compilation_msgs) {
        MessageBox(0, (LPCWSTR)compilation_msgs->GetBufferPointer(), 0, 0);
        safe_release(compilation_msgs);
    }

    if (FAILED(hr)) {
        DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
    }

    HR(D3DX11CreateEffectFromMemory(
        compiled_shader->GetBufferPointer(),
        compiled_shader->GetBufferSize(), 0,
        _device, &_fx));

    safe_release(compiled_shader);

    _tech = _fx->GetTechniqueByName("ColorTech");
    _mat_wvp = _fx->GetVariableByName("mat_wvp")->AsMatrix();
}

void dx11_preview_window::_build_vertex_layout() {
    D3D11_INPUT_ELEMENT_DESC vertex_desc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    D3DX11_PASS_DESC pass_desc;
    _tech->GetPassByIndex(0)->GetDesc(&pass_desc);
    HR(_device->CreateInputLayout(vertex_desc, 2,
        pass_desc.pIAInputSignature,
        pass_desc.IAInputSignatureSize,
        &_input_layout));
}