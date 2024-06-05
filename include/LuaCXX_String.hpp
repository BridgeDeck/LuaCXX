/**
 * @file LuaCXX_String.hpp
 * @author BridgeDeck (littlefast2@gmail.com)
 * @brief Header file for containing the `LuaCXX::String` class.
 * @version 1.0
 * @date 2024-06-05
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef LuaCXX_String_HPP
#define LuaCXX_String_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"

namespace LuaCXX
{
/**
 * @brief Handle to a Lua string
 */
class String:public Variant
{
    public:
    /**
     * @brief Converts the Lua string into a C string.
     * 
     * @return const char* 
     */
    operator const char*();
};
}

#endif