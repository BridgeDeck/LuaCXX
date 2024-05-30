#include "LuaCXX.hpp"
#include "LuaCXX_Thread.hpp"
using namespace LuaCXX;


Thread::operator Lua()
{
    return Lua(lua_tothread(L, stack_index));
}

Thread::operator lua_State*()
{
    return lua_tothread(L, stack_index);
}