#ifndef LuaCXX_Variant_HPP
#define LuaCXX_Variant_HPP

#include "LuaCXX_Common.hpp"
#include <vector>
namespace LuaCXX
{
/*
	Handle to a value on the Lua stack.
*/
class Variant
{
    friend class Lua;
	friend class Stack;

    protected:
    Variant(lua_State* th, int index);

    public:
    VariantType get_type() const;
	
	/**
	 * Conversion
	 * */
	operator bool();
	operator double();
    operator String();
    operator Table();
    operator Thread();
	operator lua_CFunction();
	template<class T>
	operator Userdata<T>()
	{
		return *((Userdata<T>*)this);
	}
	template<class T>
	operator LightUserdata<T>()
	{
		return *((LightUserdata<T>*)this);
	}
	
	lua_State* get_lua() const;
	/*
	 * Metatable operations
	 * */

	/*
		Set the metatable of this value, if it can have one.
	*/
	void set_metatable(Table mt);

	/*
		Get the metatable of this value, if it has one.
	*/
	Table get_metatable() const;

	/*
		Set the key `K` to value `V`.
		May trigger this value's `"__newindex"` metamethod if it has one.
	*/
	void set(Variant K, Variant V);

	/*
		Set the key `K` to value `V`.
		Will not trigger metamethods.
	*/
	void rawset(Variant K, Variant V);

	/*
		Get a value from key `K`.
		May trigger this value's `"__index"` metamethod if it has one.
	*/
	Variant get(Variant K);

	/*
		Get a value from key `K`.
		Will not trigger metamethods.
	*/
	Variant rawget(Variant K) const;

	/*
		Calls this value as a function or using the `"__call"` metamethod
		with the following `arguments`.
	*/
	std::vector<Variant> call(std::vector<Variant> arguments);

	/*
		Calls this value as a function or using the `"__call"` metamethod
		with the following arguments.
	*/
	template<class... Args>
	std::vector<Variant> call(Variant v, Args... a )
	{
		_tmp_args.push_back(v);
		return call(a...);
	}
	/*
		Calls this value as a function or using the `"__call"` metamethod
		with `_tmp_args` as its arguments.
		Used internally.
	*/
	std::vector<Variant> call();

	/*
		Calls this value as a function or using the `"__call"` metamethod (in protected mode)
		with `_tmp_args` as its arguments.
		Used internally.
	*/
	std::vector<Variant> pcall(Variant err_handler, int& error_code);
	
	/*
		Calls this value as a function or using the `"__call"` metamethod (in protected mode)
		with the following `arguments`.
	*/
	std::vector<Variant> pcall(Variant err_handler, int& error_code, std::vector<Variant> arguments);

	/*
		Calls this value as a function or using the `"__call"` metamethod (in protected mode)
		with the following arguments.
	*/
	template<class... Args>
	std::vector<Variant> pcall(Variant err_handler, int& error_code, Variant v, Args... a )
	{
		_tmp_args.push_back(v);
		return pcall(err_handler, error_code, a...);
	}
    protected:

	std::vector<Variant> _tmp_args;

    lua_State* L;
    int stack_index;
};
}
#endif
