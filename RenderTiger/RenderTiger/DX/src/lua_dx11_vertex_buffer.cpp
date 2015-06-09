#include "lua_dx11_vertex_buffer.h"
#include "dx11_vertex_buffer.h"

#define GET_DX11_VB(L, i) \
    (dx11_vertex_buffer*)lua_touserdata(L, i)

static int ll_new(lua_State *L) {
    dx11_vertex_buffer *vb = new dx11_vertex_buffer();
    lua_pushlightuserdata(L, vb);
    return 1;
}

static int ll_dispose(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 0);
    delete vb;
    return 0;
}

static int ll_clear(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 0);
    vb->clear();
    return 0;
}

static int ll_add_vb_element(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 0);
    float f = lua_tonumber(L, 1);
    vb->add_vb_element(f);
    return 0;
}

static int ll_add_ib_element(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 0);
    int i = lua_tointeger(L, 1);
    vb->add_ib_element(i);
    return 0;
}

int lua_dx11_vertex_buffer(lua_State *L) {
    luaL_Reg l[] = {
        { "new", ll_new },
        { "dispose", ll_dispose },
        { "clear", ll_clear },
        { "add_vb_element", ll_add_vb_element },
        { "add_ib_element", ll_add_ib_element },
        { NULL, NULL },
    };

    luaL_newlib(L, l);

    return 1;
}