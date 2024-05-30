#include "LuaCXX.hpp"

using namespace LuaCXX;

Lua::Lua(lua_State*lua)
{
    L=lua;
}

String Lua::new_string(const char *my_str)
{
    lua_pushstring(L, my_str);
    return Variant(L, lua_gettop(L));
}
