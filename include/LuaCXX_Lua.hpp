#ifndef LuaCXX_Lua_HPP
#define LuaCXX_Lua_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"

namespace LuaCXX
{
/*
    Wraps around a `lua_State*` to make it easier to use Lua from C++. 
*/
class Lua
{
	public:
	Lua(lua_State* from);

	/*
		Get the status of this thread, see `ThreadStatus` for more details.
		TODO: I don't think this method even has a definition
	*/
	ThreadStatus get_status() const;

	/*
		Get a handle to the Lua stack, see `Stack` for more information.
		TODO: Yeah I don't have Stack implemented yet, but I habe plans.
	*/
	Stack stack() const;

	/*
		Create a new string.
	*/
	String new_string(const char* my_str);

	/*
		Create a new empty table.
	*/
    Table new_table();

	/*
		Create a new thread
	*/
	Thread new_thread();

	/*
		Create a new nil value
		TODO: I just realized I have not made a test for this one yet, don't think it even has a
		definition.
	*/
	Variant new_nil();

	/*
		Create a new number value.
	*/
	Variant new_number(double n);

	/*
		Create a new boolean value.
	*/
	Variant new_boolean(bool b);

	/*
		Create a new Lua C Function handle
	*/
	Variant new_function(lua_CFunction f);

	/*
		Creates a Lua Userdata for `T` and initializes it with `args`.
	*/
	template<class T, class... InitArgs>
	Userdata<T> new_userdata(InitArgs... args)
	{
		T* new_ud = (T*)lua_newuserdata(L, sizeof(T));
		*new_ud = T(args...);
		return Variant(L, lua_gettop(L));
	}

	/*
		Creates a Lua Userdata for `T` and initializes it with an existing `T`.
	*/
	template<class T>
	Userdata<T> create_userdata(T& from)
	{
		T* new_ud = (T*)lua_newuserdata(L, sizeof(T));
		*new_ud = from;
		return Variant(L, lua_gettop(L));
	}

	/*
		Creates a Lua Light Userdata pointing to `lud`.
	*/
	template<class T>
	LightUserdata<T> new_light_userdata(T* lud)
	{
		lua_pushlightuserdata(L, (void *)lud);
		return Variant(L, lua_gettop(L));
	}

	/*
		This thread's environment
	*/
	Table environment() const;

	/*
		The Lua globals table
	*/
    Table globals() const;

	/*
		The Lua registry table
	*/
    Table registry() const;

    operator lua_State*();

	private:
	lua_State* L;

   };
}

#endif
