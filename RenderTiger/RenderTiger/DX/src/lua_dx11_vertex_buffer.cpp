#include "lua_dx11_vertex_buffer.h"
#include "dx11_vertex_buffer.h"

#define GET_DX11_VB(L, i) \
    (dx11_vertex_buffer*)lua_touserdata(L, i)

/**For test.*/
dx11_vertex_buffer *g_test_dx11_vb = nullptr;
/**End test.*/

static int ll_new(lua_State *L) {
    //NOTICE: just test.
    if (g_test_dx11_vb == nullptr)
        g_test_dx11_vb = new dx11_vertex_buffer();
    lua_pushlightuserdata(L, g_test_dx11_vb);
    return 1;
}

static int ll_dispose(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 1);
    delete vb;
    return 0;
}

static int ll_clear(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 1);
    vb->clear();
    return 0;
}

static int ll_add_vb_element(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 1);
    float f = lua_tonumber(L, 2);
    vb->add_vb_element(f);
    return 0;
}

static int ll_add_ib_element(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 1);
    int i = lua_tointeger(L, 2);
    vb->add_ib_element(i);
    return 0;
}

static int ll_add_layout_element(lua_State *L) {
    dx11_vertex_buffer *vb = GET_DX11_VB(L, 1);
    QString layout = lua_tostring(L, 2);
    vb->add_input_layout(layout);
    return 0;
}

static int ll_flush(lua_State *L) {
    return 0;
}

int lua_dx11_vertex_buffer(lua_State *L) {
    luaL_Reg l[] = {
        { "new", ll_new },
        { "dispose", ll_dispose },
        { "clear", ll_clear },
        { "add_vb_element", ll_add_vb_element },
        { "add_ib_element", ll_add_ib_element },
        { "add_layout_element", ll_add_layout_element },
        { "flush", ll_flush },
        { NULL, NULL },
    };

    luaL_newlib(L, l);

    return 1;
}