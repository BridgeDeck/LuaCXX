#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"

using namespace LuaCXX;

Variant::Variant(lua_State* lua, int index)
{
    stack_index = index;
    L = lua;
}

template<>
Variant Variant::rawget<Variant, Variant>(Variant field) const
{
    lua_pushvalue(L, field.stack_index);
    lua_rawget(L, stack_index);
    return Variant(L, lua_gettop(L));
}