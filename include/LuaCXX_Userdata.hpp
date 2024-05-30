#ifndef LuaCXX_Userdata_HPP
#define LuaCXX_Userdata_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Lua.hpp"
#include "LuaCXX_Variant.hpp"
namespace LuaCXX
{

/*
	Handle to a Lua userdata.
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
/*
	Handle to a Lua light userdata.
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
