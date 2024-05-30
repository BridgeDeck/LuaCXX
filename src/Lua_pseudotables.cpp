#include "LuaCXX_Lua.hpp"
#include "LuaCXX_Table.hpp"

using namespace LuaCXX;

Table Lua::globals() const
{
    return Table(L, LUA_GLOBALSINDEX);
}