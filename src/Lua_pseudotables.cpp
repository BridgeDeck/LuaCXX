#include "LuaCXX_Lua.hpp"
#include "LuaCXX_Table.hpp"

using namespace LuaCXX;

Table Lua::globals() const
{
    Table t = Table(L, LUA_GLOBALSINDEX);
    return t;
}