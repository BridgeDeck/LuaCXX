#ifndef LuaCXX_Lua_HPP
#define LuaCXX_Lua_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"

namespace LuaCXX
{
/*
    Primary wrapper around a `lua_State*`.    
*/
class Lua
{
	public:
	Lua(lua_State* from);

	ThreadStatus get_status() const;

	Stack stack() const;

	String new_string(const char* my_str);
    Table new_table();
	Thread new_thread();
	Variant new_nil();
	Variant new_number(double n);
	Variant new_boolean(bool b);
	Variant new_function(lua_CFunction f);

	template<class T, class... InitArgs>
	Userdata<T> new_userdata(InitArgs... args)
	{
		T* new_ud = (T*)lua_newuserdata(L, sizeof(T));
		*new_ud = T(args...);
		return Variant(L, lua_gettop(L));
	}
	template<class T>
	Userdata<T> create_userdata(T from)
	{
		T* new_ud = (T*)lua_newuserdata(L, sizeof(T));
		*new_ud = from;
		return Variant(L, lua_gettop(L));
	}
	template<class T>
	LightUserdata<T> new_light_userdata(T* lud)
	{
		lua_pushlightuserdata(L, (void *)lud);
		return Variant(L, lua_gettop(L));
	}

	Table environment() const;
    Table globals() const;
    Table registry() const;

    operator lua_State*();

	private:
	lua_State* L;

   };
}

#endif
