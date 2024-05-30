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
	operator Userdata<T>();
	template<class T>
	operator LightUserdata<T>();
	
	/*
	 * Metatable operations
	 * */

	void set_metatable(const Table& mt);
	Table get_metatable() const;

	template<class K, class V>
	void set(K, V);
	template<class K, class V>
	void rawset(K, V);

	template<class K, class V>
	V get(K);
	template<class K, class V>
	V rawget(K) const;

    protected:
    lua_State* L;
    int stack_index = 0;
};
}
#endif
