#ifndef LuaCXX_Lua_HPP
#define LuaCXX_Lua_HPP

#include "LuaCXX_Common.hpp"

namespace LuaCXX
{
/*
    Primary wrapper around a `lua_State*`.    
*/
class Lua
{
	public:
	Lua(lua_State* from);

	Stack stack() const;

	String new_string(const char* my_str);
    Table new_table();
	Thread new_thread();
	Variant new_nil();
	Variant new_number(double n);
	Variant new_boolean(bool b);
	Variant new_function(int (*func)(lua_State*));

	template<class T>
	Userdata<T> new_userdata();
	template<class T>
	LightUserdata<T> new_light_userdata(T* lud);

	Table environment() const;
    Table globals() const;
    Table registry() const;

    operator lua_State*();

	private:
	lua_State* L;

   };
}

#endif
