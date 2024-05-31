/*
    This file is for `Lua`'s methods that get the tables from Lua's pseudoindices.
*/

#include "LuaCXX_Lua.hpp"
#include "LuaCXX_Table.hpp"

using namespace LuaCXX;

Table Lua::globals() const
{
    return Table(L, LUA_GLOBALSINDEX);
}

Table Lua::registry() const
{
    return Table(L, LUA_REGISTRYINDEX);
}

Table Lua::environment() const
{
    return Table(L, LUA_ENVIRONINDEX);
}