#include "LuaCXX_Common.hpp"
#include "LuaCXX_Table.hpp"
#include "lua.h"

using namespace LuaCXX;

Table::Table(lua_State* lua, int index):Variant(lua, index)
{

}