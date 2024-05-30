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
	
	/*
	 * Metatable operations
	 * */

	/*
		Set the metatable of this value, if it can have one.
		TODO: Not defined internally :P
	*/
	void set_metatable(const Table& mt);

	/*
		Get the metatable of this value, if it has one.
		TODO: Not defined internally :hilarious skull emoji:
	*/
	Table get_metatable() const;

	/*
		Set the key `K` to value `V`.
		May trigger this value's `"__newindex"` metamethod if it has one.
		TODO: Not defined internally 
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
		TODO: Not defined internally 
	*/
	Variant get(Variant K);

	/*
		Get a value from key `K`.
		Will not trigger metamethods.
	*/
	Variant rawget(Variant K) const;

	/*
		Calls this value as a function or using the `"__call"` metamethod.
		Only to used internally.
		TODO: Not defined internally [FUCKING SHOCKER] 
	*/
	std::vector<Variant> call();
	
	/*
		Calls this value as a function or using the `"__call"` metamethod
		with the following `arguments`.
		TODO: Not defined internally 
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

    protected:
	std::vector<Variant> _tmp_args;

    lua_State* L;
    int stack_index;
};
}
#endif
