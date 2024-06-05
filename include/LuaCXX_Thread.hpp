/**
 * @file LuaCXX_String.hpp
 * @author BridgeDeck (littlefast2@gmail.com)
 * @brief Header file for containing the `LuaCXX::Thread` class.
 * @version 1.0
 * @date 2024-06-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LuaCXX_Thread_HPP
#define LuaCXX_Thread_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"
#include "LuaCXX_Lua.hpp"

namespace LuaCXX
{
/**
 * @brief Handle to a Lua thread.
 */
class Thread: public Variant
{
	friend class Lua;
	public:

	/**
	 * @brief Converts this handle to a raw Lua thread.
	 * 
	 * @return lua_State* 
	 */
	operator lua_State*();

	/**
	 * @brief Converts this handle to a new Lua wrapper;
	 * 
	 * @return Lua 
	 */
	operator Lua();
};
}
#endif
