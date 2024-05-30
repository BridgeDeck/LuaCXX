#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"
#include "lua.h"

using namespace LuaCXX;

Variant::Variant(lua_State* lua, int index)
{
    stack_index = index;
    L = lua;
}

Variant Variant::rawget(Variant key) const
{
    //key.can_be_nillified = false;
    lua_pushvalue(L, key.stack_index);
    lua_rawget(L, stack_index);
    return Variant(L, lua_gettop(L));
}

void Variant::rawset(Variant key, Variant value)
{
    //key.can_be_nillified = false;
    //value.can_be_nillified = false;
    lua_pushvalue(L, key.stack_index);
    lua_pushvalue(L, value.stack_index);
    lua_rawset(L, stack_index);
}