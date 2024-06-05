/**
 * @file LuaCXX_Lua.hpp
 * @author BridgeDeck (littlefast2@gmail.com)
 * @brief Header file for containing the `LuaCXX::Lua` class
 * @version 1.0
 * @date 2024-06-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef LuaCXX_Lua_HPP
#define LuaCXX_Lua_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"
#include "lua.h"

namespace LuaCXX
{
/**
 * @brief A wrapper for making Lua easier to work with.
 * Simply wrap it around a `lua_State*` and you are good to go.
 */
class Lua
{
	public:
	/**
	 * @brief Construct a new Lua instance from a raw `lua_State*`
	 * 
	 * @param from 
	 */
	Lua(lua_State* from);

	/**
	 * @brief Get the status of this Lua thread (Unused for now)
	 * 
	 * @return ThreadStatus 
	 */
	ThreadStatus get_status() const;

	/**
	 * @brief Get a handle to the Stack.
	 * 
	 * @return Stack 
	 */
	Stack stack() const;

	/**
	 * @brief Create a new string.
	 * 
	 * @param str : The standard string to create this string from.
	 * @return String : Handle to the new string.
	 */
	String new_string(const char* str);

	/**
	 * @brief Create a new empty table
	 * 
	 * @return Table : Handle to the new table
	 */
    Table new_table();

	/**
	 * @brief Create a new thread.
	 * 
	 * @return Thread : handle to the new thread.
	 */
	Thread new_thread();

	/**
	 * @brief Create a new nil value.
	 * 
	 * @return Variant : Handle to the new value.
	 */
	Variant new_nil();

	/**
	 * @brief Create a new number value.
	 * 
	 * @param n : Number to create this value from.
	 * @return Variant 
	 */
	Variant new_number(double n);

	/**
	 * @brief Create a new boolean value.
	 * 
	 * @param b : Boolean to create this value from.
	 * @return Variant 
	 */
	Variant new_boolean(bool b);

	/**
	 * @brief Create a new Lua CFunction.
	 * 
	 * @param f : Pointer to a valid lua_CFunction.
	 * @return Variant 
	 */
	Variant new_function(lua_CFunction f);

	/**
	 * @brief Initializes a new `T` instance as a Lua userdata.
	 * 
	 * @tparam T : The class to create a Userdata from.
	 * @tparam InitArgs : See `args`.
	 * @param args : Arguments for initializing `T`.
	 * @return Userdata<T> 
	 */
	template<class T, class... InitArgs>
	Userdata<T> new_userdata(InitArgs... args)
	{
		T* new_ud = (T*)lua_newuserdata(L, sizeof(T));
		*new_ud = T(args...);
		return Variant(L, lua_gettop(L));
	}

	/**
	 * @brief Create a Userdata based on an existing instance of `T`
	 * 
	 * @tparam T : The class to create a Userdata from.
	 * @param from : Reference to an existing instance of `T`.
	 * @return Userdata<T> 
	 */
	template<class T>
	Userdata<T> create_userdata(T& from)
	{
		T* new_ud = (T*)lua_newuserdata(L, sizeof(T));
		*new_ud = from;
		return Variant(L, lua_gettop(L));
	}

	/**
	 * @brief Create a Light Userdata
	 * 
	 * @tparam T : The class to create a Light Userdata from.
	 * @param lud : Pointer to an instance of `T`.
	 * @return LightUserdata<T> 
	 */
	template<class T>
	LightUserdata<T> new_light_userdata(T* lud)
	{
		lua_pushlightuserdata(L, (void *)lud);
		return Variant(L, lua_gettop(L));
	}

	// Code for Lua 5.1 and LuaJIT only
	#if !(LUA_VERSION_NUM > 501)

	/**
	 * @brief Returns this thread's environment table.
	 * @warning Not compatible with Lua 5.2 and later, will return a nil.
	 * @return Table 
	 */
	Table environment();

	#endif // LUA_VERSION_NUM > 501

	/**
	 * @brief Returns Lua's global table.
	 * 
	 * @return Table 
	 */
    Table globals() const;

	/**
	 * @brief Returns Lua's registry table.
	 * 
	 * @return Table 
	 */
    Table registry() const;

	/**
	 * @brief Creates a Lua chunk from Lua source code.
	 * 
	 * @param lua_source_code : Text containing Lua source code.
	 * @param chunkname : A human-readable name for debugging purposes.
	 * @return Variant : Can be called as a function using `Variant::call` or `Variant::pcall`.
	 */
	Variant compile(const char* lua_source_code, const char* chunkname="");

	/**
	 * @brief Get the wrapped `lua_State*`.
	 * 
	 * @return lua_State* 
	 */
    operator lua_State*();

	private:
	/** @internal
	 * @brief The Lua state, where all the magic of Lua happens.
	 */
	lua_State* L;

   };
}

#endif
