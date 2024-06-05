/**
 * @file LuaCXX_String.hpp
 * @author BridgeDeck (littlefast2@gmail.com)
 * @brief Header file for containing the `LuaCXX::Table` class.
 * @version 1.0
 * @date 2024-06-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LuaCXX_Table_HPP
#define LuaCXX_Table_HPP

#include "LuaCXX_Variant.hpp"
#include "LuaCXX_Common.hpp"
namespace LuaCXX
{
/**
 * @brief Handle to a Lua table.
 */
class Table: public Variant
{
    friend class Lua;
    friend class Variant;

	protected:
	Table(lua_State* lua, int stack_index);
};
}
#endif
