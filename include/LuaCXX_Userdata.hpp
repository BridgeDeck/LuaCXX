#ifndef LuaCXX_Userdata_HPP
#define LuaCXX_Userdata_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Lua.hpp"
#include "LuaCXX_Variant.hpp"
namespace LuaCXX
{
template<class T>
class Userdata:public Variant
{
	friend class Lua;
	private:

	public:
	T operator->()
	{
		if (lua_type(L, stack_index) == LUA_TUSERDATA)
			return *lua_touserdata(L, stack_index);
		else
			return reinterpret_cast<T>((unsigned char[sizeof(Userdata<T>)]){0});
	}
};

template<class T>
class LightUserdata:public Variant
{
	friend class Lua;
	public:
	T operator->()
	{
		if (lua_type(L, stack_index) == LUA_TLIGHTUSERDATA)
			return *lua_touserdata(L, stack_index);
		else
			return reinterpret_cast<T>((unsigned char[sizeof(LightUserdata<T>)]){0});
	}
};
}

#endif
