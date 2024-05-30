#include "LuaCXX_Variant.hpp"
#include "LuaCXX_String.hpp"
#include "LuaCXX_Table.hpp"
using namespace LuaCXX;

Variant::operator String()
{
    return *((String*)this);
}
Variant::operator Table()
{
    return *((Table*)this);
}
Variant::operator bool()
{
    if (lua_type(L, stack_index) != LUA_TBOOLEAN)
        return false;

    if (lua_toboolean(L, stack_index))
        return true;
    else
        return false;
}
Variant::operator double()
{
    if (lua_type(L, stack_index) != LUA_TNUMBER)
        return 0.0;
    return lua_tonumber(L, stack_index);
}