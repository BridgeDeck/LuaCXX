#ifndef LuaCXX_Table_HPP
#define LuaCXX_Table_HPP

#include "LuaCXX_Variant.hpp"
#include "LuaCXX_Common.hpp"
namespace LuaCXX
{
/*
	Handle to an internal Lua table.
*/
class Table: public Variant
{
    friend class Lua;

	protected:
	Table(lua_State* lua, int stack_index);
};
}
#endif
