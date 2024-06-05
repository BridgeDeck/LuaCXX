/**
 * @file LuaCXX_Common.hpp
 * @author BridgeDeck (littlefast2@gmail.com)
 * @brief A header file for containing forward declarations and constants/enumerations.
 * @version 1.0
 * @date 2024-06-04
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef LuaCXX_Common_HPP
#define LuaCXX_Common_HPP

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}

namespace LuaCXX
{

/**
 * @brief Enumeration for the type of a Variant.
 * Corresponds to the type a value on the Lua stack can be.
 */
typedef enum VariantType{
    BOOLEAN=LUA_TBOOLEAN,
    NUMBER=LUA_TNUMBER,
    STRING=LUA_TSTRING,
    TABLE=LUA_TTABLE,
    USERDATA=LUA_TUSERDATA,
    LIGHTUSERDATA=LUA_TLIGHTUSERDATA,
    THREAD=LUA_TTHREAD,
    NIL=LUA_TNIL,
    FUNCTION=LUA_TFUNCTION,
    NONE=LUA_TNONE
} VariantType;

/**
 * @brief Status of a thread (Unused for now)
 */
typedef enum ThreadStatus{
	Yield,
	Ended,
	Error
} ThreadStatus;

/**************************
 *  Forward Declarations  *
 **************************/

class Lua;
class Variant;
class Thread;
class Table;
class String;
class Stack;

template<class T>
class LightUserdata;
template<class T>
class Userdata;

}
#endif
