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

/*
    The type of Lua value that a Variant is.
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

/*
    Status of a running thread.
    `Yield`: This thread is yielding and has not finished.
    `Ended`: This thread has finished.
    `Error`: This thread finished prematurely with an error.
*/
typedef enum ThreadStatus{
	Yield,
	Ended,
	Error
} ThreadStatus;

/*
    Forward declarations
*/

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
