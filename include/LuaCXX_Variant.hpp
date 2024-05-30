#ifndef LuaCXX_Variant_HPP
#define LuaCXX_Variant_HPP

#include "LuaCXX_Common.hpp"
#include <vector>
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

	void set_metatable(const Table& mt);
	Table get_metatable() const;

	void set(Variant K, Variant V);
	void rawset(Variant K, Variant V);
	Variant get(Variant K);
	Variant rawget(Variant K) const;

	std::vector<Variant> call();
	
	std::vector<Variant> call(std::vector<Variant> args);

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
