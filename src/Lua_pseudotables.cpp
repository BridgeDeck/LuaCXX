/*
    This file is for `Lua`'s methods that get the tables from Lua's pseudoindices.
*/

#include "LuaCXX_Lua.hpp"
#include "LuaCXX_Table.hpp"
#include "Internal.hpp"

using namespace LuaCXX;

Table Lua::globals() const
{
    DBG("Table Lua::globals() const");
    return Table(L, LUA_GLOBALSINDEX);
}

Table Lua::registry() const
{
    DBG("Table Lua::registry() const");
    return Table(L, LUA_REGISTRYINDEX);
}

Table Lua::environment()
{
    DBG("Table Lua::environment()");
    #if LUA_VERSION_NUM > 501
    return (Table)new_nil();
    #else
    return Table(L, LUA_ENVIRONINDEX);
    #endif
}