#include "lua_global_msg.h"

#include "global_msg.h"

#define GET_GEM(L, i) \
    (global_msg*)lua_touserdata(L, i)

static int ll_new(lua_State *L) {
    global_msg *gem = global_msg::get_instance();
    lua_pushlightuserdata(L, gem);
    return 1;
}

static int ll_add_error(lua_State *L) {
    global_msg *gem = GET_GEM(L, 1);
    const char *msg = lua_tostring(L, 2);
    if (msg == nullptr)
        return 0;
    gem->add_error_msg(msg);
    return 0;
}

static int ll_add_info(lua_State *L) {
    global_msg *gem = GET_GEM(L, 1);
    const char *msg = lua_tostring(L, 2);
    if (msg == nullptr)
        return 0;
    gem->add_info_msg(msg);
    return 0;
}

int lua_global_msg(lua_State *L) {
    luaL_Reg l[] = {
        { "new", ll_new },
        { "add_error", ll_add_error },
        { "add_info", ll_add_info },
        { NULL, NULL }
    };

    luaL_newlib(L, l);

    return 1;
}