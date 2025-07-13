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

    public:
    static constexpr const char* METAMETHOD_ADD = "__add";
	static constexpr const char* METAMETHOD_SUBTRACT = "__sub";
	static constexpr const char* METAMETHOD_MULTIPLY = "__mul";
	static constexpr const char* METAMETHOD_DIVIDE = "__div";
	static constexpr const char* METAMETHOD_NEGATION = "__unm";
	static constexpr const char* METAMETHOD_MODULO = "__mod";
	static constexpr const char* METAMETHOD_EXPONENT = "__pow";

	static constexpr const char* METAMETHOD_EQUAL = "__eq";
	static constexpr const char* METAMETHOD_LESSTHAN = "__lt";
	static constexpr const char* METAMETHOD_LESSTHAN_EQUALTO = "__le";

	static constexpr const char* METAMETHOD_CONCAT = "__concat";
	static constexpr const char* METAMETHOD_LENGTH = "__len";

	static constexpr const char* METAMETHOD_INDEX = "__index";
	static constexpr const char* METAMETHOD_NEWINDEX = "__newindex";

	static constexpr const char* METAMETHOD_CALL = "__call";
	
	static constexpr const char* METAMETHOD_TOSTRING = "__tostring";

	protected:
	Table(lua_State* lua, int stack_index);
};
}
#endif
