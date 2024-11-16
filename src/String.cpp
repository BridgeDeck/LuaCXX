#include "LuaCXX_String.hpp"
#include "Internal.hpp"

using namespace LuaCXX;

String::operator const char *()
{
    DBG("String::operator const char *()");
    if (lua_type(L, stack_index) == LUA_TSTRING)
        return lua_tolstring(L, stack_index, 0);
    else
        return 0;
}