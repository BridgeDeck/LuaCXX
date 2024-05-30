/*
    This file is for `Lua`'s methods that get the tables from Lua's pseudoindices.
*/

#include "LuaCXX_Lua.hpp"
#include "LuaCXX_Table.hpp"

using namespace LuaCXX;

Table Lua::globals() const
{
    Table t = Table(L, LUA_GLOBALSINDEX);
    return t;
}