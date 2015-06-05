#include "render_triger_main_window.h"

#include <assert.h>
#include <QMouseEvent>

struct Vertex {
    XMFLOAT3 Pos;
    XMFLOAT4 Color;
};

bool render_triger_main_window::init() {
    if (!qt5_dx11_app_framework::init())
        return false;
    build_vertex_buffer();
    build_fx();
    build_vertex_layout();

    return true;
}

void render_triger_main_window::on_resize() {
    qt5_dx11_app_framework::on_resize();

    //The windows resized, so update the aspect ratio and recomputed the projection matrix.
    XMMATRIX P = XMMatrixPerspectiveFovLH(0.25f * XM_PI, get_aspect_radio(), 1.0f, 1000.0f);
    XMStoreFloat4x4(&_mat_proj, P);
}

void render_triger_main_window::on_update() {
    //Convert Spherical to Cartesian coordinates.
    float x = _radius * sinf(_phi) * cosf(_theta);
    float z = _radius * sinf(_phi) * sinf(_theta);
    float y = _radius * cosf(_phi);

    //Build the view matrix.
    XMVECTOR pos = XMVectorSet(x, y, z, 1.0f);
    XMVECTOR target = XMVectorZero();
    XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

    XMMATRIX V = XMMatrixLookAtLH(pos, target, up);
    XMStoreFloat4x4(&_mat_view, V);
}

void render_triger_main_window::on_draw() {
    _context->ClearRenderTargetView(_render_target_view, reinterpret_cast<const float*>(&Colors::Black));
    _context->ClearDepthStencilView(_depth_stencil_view, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    _context->IASetInputLayout(_input_layout);
    _context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    _context->IASetVertexBuffers(0, 1, &_box_vb, &stride, &offset);
    _context->IASetIndexBuffer(_box_ib, DXGI_FORMAT_R32_UINT, 0);

    //Set constants.
    XMMATRIX world = XMLoadFloat4x4(&_mat_world);
    XMMATRIX view = XMLoadFloat4x4(&_mat_view);
    XMMATRIX proj = XMLoadFloat4x4(&_mat_proj);
    XMMATRIX worldViewProj = world * view * proj;

    _mat_wvp->SetMatrix(reinterpret_cast<float*>(&worldViewProj));

    D3DX11_TECHNIQUE_DESC tech_desc;
    _tech->GetDesc(&tech_desc);
    for (UINT p = 0; p < tech_desc.Passes; p++) {
        _tech->GetPassByIndex(p)->Apply(0, _context);

        //36 indices for the box.
        _context->DrawIndexed(36, 0, 0);
    }

    HR(_swap_chain->Present(0, 0));
}

void render_triger_main_window::on_keyborad(QKeyEvent *event) {

}

void render_triger_main_window::on_mouse_press(QMouseEvent *event) {
    _last_mouse_pos.x = event->x();
    _last_mouse_pos.y = event->y();
    _mouse_btn_when_pressed = event->button();
    SetCapture(get_win_hwnd());
}

void render_triger_main_window::on_mouse_release(QMouseEvent *event) {
    ReleaseCapture();
}

template<typename T>
static T _clamp(const T& x, const T& low, const T& high) {
    return x < low ? low : (x > high ? high : x);
}

void render_triger_main_window::on_mouse_move(QMouseEvent *event) {
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

void render_triger_main_window::build_vertex_buffer() {
    //Create Vertex Buffer.
    Vertex vertices[] = {
        { XMFLOAT3(-1.0f, -1.0f, -1.0f), reinterpret_cast<const float*>(&Colors::White) },
        { XMFLOAT3(-1.0f, +1.0f, -1.0f), reinterpret_cast<const float*>(&Colors::Black) },
        { XMFLOAT3(+1.0f, +1.0f, -1.0f), reinterpret_cast<const float*>(&Colors::Red) },
        { XMFLOAT3(+1.0f, -1.0f, -1.0f), reinterpret_cast<const float*>(&Colors::Green) },
        { XMFLOAT3(-1.0f, -1.0f, +1.0f), reinterpret_cast<const float*>(&Colors::Blue) },
        { XMFLOAT3(-1.0f, +1.0f, +1.0f), reinterpret_cast<const float*>(&Colors::Yellow) },
        { XMFLOAT3(+1.0f, +1.0f, +1.0f), reinterpret_cast<const float*>(&Colors::Cyan) },
        { XMFLOAT3(+1.0f, -1.0f, +1.0f), reinterpret_cast<const float*>(&Colors::Magenta) }
    };

    D3D11_BUFFER_DESC vbd;
    vbd.Usage = D3D11_USAGE_IMMUTABLE;
    vbd.ByteWidth = sizeof(Vertex)* 8;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbd.CPUAccessFlags = 0;
    vbd.MiscFlags = 0;
    vbd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA vinitData;
    vinitData.pSysMem = vertices;
    HR(_device->CreateBuffer(&vbd, &vinitData, &_box_vb));

    //Create the index buffer.
    UINT indices[] = {
        //front.
        0, 1, 2,
        0, 2, 3,
        //back.
        4, 6, 5,
        4, 7, 6,
        //left.
        4, 5, 1,
        4, 1, 0,
        //right.
        3, 2, 6,
        3, 6, 7,
        //top.
        1, 5, 6,
        1, 6, 2,
        //bottom.
        4, 0, 3,
        4, 3, 7
    };
    D3D11_BUFFER_DESC ibd;
    ibd.Usage = D3D11_USAGE_IMMUTABLE;
    ibd.ByteWidth = sizeof(UINT)* 36;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.CPUAccessFlags = 0;
    ibd.MiscFlags = 0;
    ibd.StructureByteStride = 0;
    D3D11_SUBRESOURCE_DATA iinitData;
    iinitData.pSysMem = indices;
    HR(_device->CreateBuffer(&ibd, &iinitData, &_box_ib));
}

void render_triger_main_window::build_fx() {
    DWORD shaderFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
    shaderFlags |= D3D10_SHADER_DEBUG;
    shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

    ID3D10Blob *compiled_shader = 0;
    ID3D10Blob *compilation_msgs = 0;
    HRESULT hr = D3DX11CompileFromFile(L"TestFX/color.fx", 0, 0, 0, "fx_5_0", shaderFlags,
        0, 0, &compiled_shader, &compilation_msgs, 0);
    if (compilation_msgs) {
        MessageBox(0, (LPCWSTR)compilation_msgs->GetBufferPointer(), 0, 0);
        safe_release(compilation_msgs);
    }

    //Even if there are no compilationMsgs, check to make sure there were no other errors.
    if (FAILED(hr)) {
        DXTrace(__FILE__, (DWORD)__LINE__, hr, L"D3DX11CompileFromFile", true);
    }

    HR(D3DX11CreateEffectFromMemory(
        compiled_shader->GetBufferPointer(),
        compiled_shader->GetBufferSize(), 0,
        _device, &_fx));

    //Done with compiled shader.
    safe_release(compiled_shader);

    _tech = _fx->GetTechniqueByName("ColorTech");
    _mat_wvp = _fx->GetVariableByName("gWorldViewProj")->AsMatrix();
}

void render_triger_main_window::build_vertex_layout() {
    //Create the vertex input layout.
    D3D11_INPUT_ELEMENT_DESC vertex_desc[] = {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    //Create the input layout.
    D3DX11_PASS_DESC pass_desc;
    _tech->GetPassByIndex(0)->GetDesc(&pass_desc);
    HR(_device->CreateInputLayout(vertex_desc, 2,
        pass_desc.pIAInputSignature,
        pass_desc.IAInputSignatureSize,
        &_input_layout));
}

render_triger_main_window::render_triger_main_window(QWidget *parent)
: qt5_dx11_app_framework(parent),
_box_vb(0), _box_ib(0), _fx(0), _tech(0),
_mat_wvp(0), _input_layout(0),
_theta(1.5f * XM_PI), _phi(0.25f * XM_PI), _radius(5.0f) {
    ui.setupUi(this);

    XMMATRIX I = XMMatrixIdentity();
    XMStoreFloat4x4(&_mat_world, I);
    XMStoreFloat4x4(&_mat_view, I);
    XMStoreFloat4x4(&_mat_proj, I);

    assert(init());
    run();
}

render_triger_main_window::~render_triger_main_window() {
    safe_release(_box_vb);
    safe_release(_box_ib);
    safe_release(_fx);
    safe_release(_input_layout);
}