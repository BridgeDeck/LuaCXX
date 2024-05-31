#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"

using namespace LuaCXX;

Lua::Lua(lua_State*lua)
{
    L=lua;
}

ThreadStatus Lua::get_status()const
{
    ThreadStatus r = ThreadStatus::Ended;
    switch (lua_status(L)) {
        case LUA_YIELD:
        r=ThreadStatus::Yield;
        break;
        case 0:
        r=ThreadStatus::Ended;
        break;
        default:
        r=ThreadStatus::Error;
        break;
    }
    return r;
}
Variant Lua::compile(const char *lua_source_code)
{
    luaL_loadstring(L, lua_source_code);
    return Variant(L, lua_gettop(L));
}
Stack Lua::stack() const
{
    return Stack(L);
}
Lua::operator lua_State *()
{
    return L;
}