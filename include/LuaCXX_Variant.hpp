#ifndef LuaCXX_Variant_HPP
#define LuaCXX_Variant_HPP

#include "LuaCXX_Common.hpp"

namespace LuaCXX
{

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
	operator Function();
	template<class T>
	operator Userdata<T>()
	{
		Userdata<T> u;
		u.stack_index = stack_index;
		u.L = L;
		return u;
	}
	template<class T>
	operator LightUserdata<T>()
	{
		LightUserdata<T> u;
		u.stack_index = stack_index;
		u.L = L;
		return u;
	}
	
	/*
	 * Metatable operations
	 * */

	void set_metatable(const Table& mt);
	Table get_metatable() const;

	void set(Variant K, Variant V);
	void rawset(Variant K, Variant V);
	Variant get(Variant K);
	Variant rawget(Variant K) const;

    protected:

    lua_State* L;
    int stack_index;
};
}
#endif
