/**
 * @file LuaCXX_String.hpp
 * @author BridgeDeck (littlefast2@gmail.com)
 * @brief Header file for containing the `LuaCXX::Variant` class.
 * @version 1.0
 * @date 2024-06-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LuaCXX_Variant_HPP
#define LuaCXX_Variant_HPP

#include "LuaCXX_Common.hpp"
#include <vector>
namespace LuaCXX
{
/**
 * @brief General-purpose handle to a value on the Lua stack.
 */
class Variant
{
  friend class Lua;
	friend class Stack;

  protected:
  Variant(lua_State* th, int index);

  public:
	Variant();
	~Variant();

	// Variant(const char*);
	// Variant(bool);
	// Variant(double);
	// Variant(lua_CFunction);
	
  template<class T>
	Variant(T* lud):Variant()
	{
		L=luaL_newstate();
    lua_pushlightuserdata(L, lud);
    stack_index=lua_gettop(L);
	}
  template<class T, typename... Variadic>
  Variant(Variadic... args)
  {
    L=luaL_newstate();
    lua_newuserdata(L, sizeof(T));
    stack_index=lua_gettop(L);

    (*(T*)lua_touserdata(L, stack_index))=T(args...);
  }



	/**
	 * @brief Get the type of value this variant is.
	 * 
	 * @return VariantType 
	 */
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
	
	/**
	 * @brief Get the `lua_State*` that this variant exists on.
	 * 
	 * @return lua_State* 
	 */
	lua_State* get_lua() const;
	/*
	 * Metatable operations
	 * */

	/**
	 * @brief Set the metatable of this value, if it can have one.
	 * 
	 * @param mt : Table containing metamethods.
	 */
	void set_metatable(Table mt);

	/**
	 * @brief Get the metatable of this value, if it has one.
	 * 
	 * @return Table : Table containing metamethods.
	 */
	Table get_metatable() const;

	/**
	 * @brief Set the key `K` to value `V`.
	 * May trigger this value's `"__newindex"` metamethod if it has one.
	 *
	 * @param K
	 * @param V
	 */
	void set(Variant K, Variant V);

	/**
	 * @brief Set the key `K` to value `V` without triggering metamethods.
	 * 
	 * @param K 
	 * @param V 
	 */
	void rawset(Variant K, Variant V);

	/**
	 * @brief Get a value from key `K`.
	 * 
	 * @param K 
	 * @return Variant 
	 */
	Variant get(Variant K);

	/**
	 * @brief Get a value from key `K` without triggering metamethods.
	 * 
	 * @param K 
	 * @return Variant 
	 */
	Variant rawget(Variant K) const;

	/**
	 * @brief Calls this value as a function.
	 * 
	 * @param arguments 
	 * @return std::vector<Variant> 
	 */
	std::vector<Variant> call(std::vector<Variant> arguments);

	/**
	 * @brief Calls this value as a function.
	 * 
	 * @tparam Args 
	 * @param v 
	 * @param a 
	 * @return std::vector<Variant> 
	 */
	template<class... Args>
	std::vector<Variant> call(Variant v, Args... a )
	{
		_tmp_args.push_back(v);
		return call(a...);
	}

	/**
	 * @brief Calls this value as a function.
	 * 
	 * @return std::vector<Variant> 
	 */
	std::vector<Variant> call();

	/**
	 * @brief Calls this value as a function in protected mode.
	 * 
	 * @param err_handler Handle to a function that handles errors.
	 * @param error_code Where to put an error code.
	 * @return std::vector<Variant> 
	 */
	std::vector<Variant> pcall(Variant err_handler, int& error_code);
	
	/**
	 * @brief Calls this value as a function in protected mode.
	 * 
	 * @param err_handler Handle to a function that handles errors.
	 * @param error_code Where to put an error code.
	 * @param arguments 
	 * @return std::vector<Variant> 
	 */
	std::vector<Variant> pcall(Variant err_handler, int& error_code, std::vector<Variant> arguments);

	/**
	 * @brief Calls this value as a function in protected mode.
	 * 
	 * @tparam Args 
	 * @param err_handler Handle to a function that handles errors.
	 * @param error_code Where to put an error code.
	 * @param v 
	 * @param a 
	 * @return std::vector<Variant> 
	 */
	template<class... Args>
	std::vector<Variant> pcall(Variant err_handler, int& error_code, Variant v, Args... a )
	{
		_tmp_args.push_back(v);
		return pcall(err_handler, error_code, a...);
	}

	/**
	 * @brief Get this variant's environment, if it has one.
	 * 
	 * @return Table 
	 */
	Table get_environment() const;

	/**
	 * @brief Set this variant's environment, if it can have one.
	 * 
	 * @param env 
	 */
	void set_environment(Table& env);
	/**
	 * @brief If this points to a chunk, this will dump it as bytecode.
	 * @warning DOES NOT WORK YET.
	 * @param into 
	 */
	void dump(std::vector<char>& into);

	/**
	 * @brief Iterates to the next element in this variant based on `key`.
	 * 
	 * @param key 
	 * @param value 
	 * @return true : Can continue iterating.
	 * @return false : Reached the end of the table.
	 */
	bool next(Variant& key, Variant& value);

    protected:

	/** @internal
	 * @brief Used internally to create a copy of this value and move the copy into another stack.
	 * 
	 * @param Linto The Lua state to copy this value into
	 */
	void copyvalue_into(lua_State* Linto);

	/** @internal
	 * @brief A temporary buffer for storing `call` or `pcall` arguments.
	 * 
	 */
	std::vector<Variant> _tmp_args;

	/** @internal
	 * @brief Lua's wacky funhouse of magic.
	 * 
	 */
    lua_State* L;

	bool is_state_internal;

	/** @internal
	 * @brief The position that the value this variant points to on the Lua stack.
	 * 
	 */
    int stack_index;
};
}
#endif
