#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"

using namespace LuaCXX;

void Variant::set_metatable(Table mt)
{
    if (
        get_type()!=VariantType::TABLE &&
        get_type()!=VariantType::USERDATA
    )
        return;
    lua_pushvalue(L, mt.stack_index);
    lua_setmetatable(L, stack_index);
}

Table Variant::get_metatable() const
{
    lua_getmetatable(L, stack_index);
    return Variant(L, lua_gettop(L));
}