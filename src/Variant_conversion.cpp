/*
    This source file is specifically for `Variant`'s conversion method.
*/

#include "LuaCXX_Variant.hpp"
#include "LuaCXX_String.hpp"
#include "LuaCXX_Table.hpp"
#include "LuaCXX_Thread.hpp"
#include "Internal.hpp"
using namespace LuaCXX;

Variant::operator String()
{
    DBG("Variant::operator String()");
    return *((String*)this);
}
Variant::operator Table()
{
    DBG("Variant::operator Table()");
    return *((Table*)this);
}
Variant::operator bool()
{
    DBG("Variant::operator bool()");
    if (lua_type(L, stack_index) != LUA_TBOOLEAN)
        return false;

    if (lua_toboolean(L, stack_index))
        return true;
    else
        return false;
}
Variant::operator double()
{
    DBG("Variant::operator double()");
    if (lua_type(L, stack_index) != LUA_TNUMBER)
        return 0.0;
    return lua_tonumber(L, stack_index);
}

Variant::operator Thread()
{
    DBG("Variant::operator Thread()");
    return *((Thread*)this);
}
Variant::operator lua_CFunction()
{
    DBG("Variant::operator lua_CFunction()");
    return lua_tocfunction(L, stack_index);
}