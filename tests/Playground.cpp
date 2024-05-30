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

using namespace std;
using namespace LuaCXX;

struct a{int a;};
int main()
{
    lua_State* L=luaL_newstate();
	cout << lua_gettop(L) << endl;
	lua_newthread(L);
	cout << lua_gettop(L) << endl;
	lua_tothread(L, -1);
	cout << lua_gettop(L) << endl;
    lua_close(L);
    {
        cout << sizeof(Userdata<void>) << endl;
        cout << sizeof(Userdata<struct a>) << endl;
        cout << sizeof(Variant) << endl;
        cout << sizeof(Table) << endl;
        cout << sizeof(String) << endl;
    }
    return 0;
}
