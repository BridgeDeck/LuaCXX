#include "LuaCXX_Common.hpp"
#include "LuaCXX_Table.hpp"
#include "Internal.hpp"

using namespace LuaCXX;

Table::Table(lua_State* lua, int index):Variant(lua, index)
{
    DBG("Table::Table(lua_State* lua, int index):Variant(lua, index)");
}