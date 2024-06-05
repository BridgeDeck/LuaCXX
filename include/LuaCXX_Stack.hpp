/**
 * @file LuaCXX_Stack.hpp
 * @author BridgeDeck (littlefast2@gmail.com)
 * @brief Header file for containing the `LuaCXX::Stack` class.
 * @version 1.0
 * @date 2024-06-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LuaCXX_Stack_HPP
#define LuaCXX_Stack_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"
#include <vector>
namespace LuaCXX
{

/**
 * @brief A handle for reading the Lua stack and simplifying returning values.
 * 
 */
class Stack
{
    friend class Lua;
    private:
    Stack(lua_State* lua);
    public:

    /**
     * @brief Get a part of the stack as a Variant.
     * 
     * @param index : Which part of the stack.
     * @return Variant : Not guaranteed to be a non-nil value, or even within the stack at all.
     */
    Variant operator[](int index) const;

    /**
     * @brief Get a handle to every value on the stack.
     * 
     * @return std::vector<Variant> : Array containing the handle to every value.
     */
    std::vector<Variant> as_array() const;

    /**
     * @brief Used at the end of a lua_CFunction to indicate what to push as return values.
     * 
     * @param return_values
     * @return int : How many values Lua will read from the stack as return values.
     */
    int _return(std::vector<Variant> return_values);

    /**
     * @brief Used at the end of a lua_CFunction to indicate what to push as return values.
     * 
     * @tparam ReturnValues 
     * @param v 
     * @param vv 
     * @return int : How many values Lua will read from the stack as return values.
     */
    template<class... ReturnValues>
    int _return(Variant v, ReturnValues... vv)
    {
        _tmp_return_values.push_back(v);
        return _return(vv...);
    }

    /**
     * @brief Used at the end of a lua_CFunction to indicate what to push as return values.
     * 
     * @return int : How many values Lua will read from the stack as return values.
     */
    int _return();

    private:
    /** @internal
     * @brief A temporary buffer for storing return values.
     */
    std::vector<Variant> _tmp_return_values = {};

    /** @internal
     * @brief A Lua state where Lua does its magic tricks.
     */
    lua_State* L;
};

}

#endif