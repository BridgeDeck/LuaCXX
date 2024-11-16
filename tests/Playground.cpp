#include "LuaCXX_Common.hpp"
#include <cstdio>
#include <iostream>
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}
#include "LuaCXX.hpp"
#include "testing.h"

using namespace std;
using namespace LuaCXX;

struct a{int a;};
int void_func(lua_State* L)
{
    return 0;
}
int main()
{
    lua_State* L=luaL_newstate();
    {
        auto L1 = luaL_newstate();
        auto L2 = luaL_newstate();
        auto L3 = luaL_newstate();

        lua_pushcclosure(L1, _lua_print_func, 0);
        
        lua_pushstring(L2, "Hello ");
        lua_pushstring(L3, "World\n");
        lua_xmove(L2, L1, 1);
        lua_xmove(L3, L1, 1);

        lua_call(L1, 2, LUA_MULTRET);

        lua_close(L1);
        lua_close(L2);
        lua_close(L3);
    }

    lua_close(L);
    {
        cout << sizeof(Lua) << endl;
        cout << sizeof(Userdata<void>) << endl;
        cout << sizeof(Userdata<struct a>) << endl;
        cout << sizeof(Variant) << endl;
        cout << sizeof(Table) << endl;
        cout << sizeof(String) << endl;
    }
    return 0;
}
