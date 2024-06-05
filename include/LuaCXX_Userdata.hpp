/**
 * @file LuaCXX_String.hpp
 * @author BridgeDeck (littlefast2@gmail.com)
 * @brief Header file for containing the `LuaCXX::Userdata` and `LuaCXX::LightUserdata` classes.
 * @version 1.0
 * @date 2024-06-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LuaCXX_Userdata_HPP
#define LuaCXX_Userdata_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Lua.hpp"
#include "LuaCXX_Variant.hpp"
namespace LuaCXX
{

/**
 * @brief Handle to a Userdata that represents `T`.
 * 
 * @tparam T 
 */
template<class T>
class Userdata:public Variant
{
	friend class Lua;
	private:

	public:
	T* operator->()
	{
		return (T*)(*this);
	}
	operator T*()
	{
		if (lua_type(L, stack_index) == LUA_TUSERDATA)
			return (T*)lua_touserdata(L, stack_index);
		else
			return 0;

	}
};
/**
 * @brief Handle to a LightUserdata that represents `T`.
 * 
 * @tparam T 
 */
template<class T>
class LightUserdata:public Variant
{
	friend class Lua;
	public:
	T* operator->()
	{
		return (T*)(*this);
	}
	operator T*()
	{
		if (lua_type(L, stack_index) == LUA_TLIGHTUSERDATA)
			return (T*)lua_touserdata(L, stack_index);
		else
			return 0;
	}
};
}

#endif
