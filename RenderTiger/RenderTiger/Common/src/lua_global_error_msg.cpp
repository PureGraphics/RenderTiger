#include "lua_global_error_msg.h"

#include "global_error_msg.h"

#define GET_GEM(L, i) \
    (global_error_msg*)lua_touserdata(L, i)

static int ll_new(lua_State *L) {
    global_error_msg *gem = global_error_msg::get_instance();
    lua_pushlightuserdata(L, gem);
    return 1;
}

static int ll_add(lua_State *L) {
    global_error_msg *gem = GET_GEM(L, 1);
    const char *msg = lua_tostring(L, 2);
    gem->add_error_msg(msg);
    return 0;
}

int lua_global_error_msg(lua_State *L) {
    luaL_Reg l[] = {
        { "new", ll_new },
        { "add", ll_add },
        { NULL, NULL }
    };

    luaL_newlib(L, l);

    return 1;
}