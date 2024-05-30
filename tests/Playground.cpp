#include <cstdio>
#include <iostream>
extern "C"
{
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

using namespace std;

int main()
{
    lua_State* L=luaL_newstate();
	cout << lua_gettop(L);
	lua_newthread(L);
	cout << lua_gettop(L);
	lua_tothread(L, -1);
	cout << lua_gettop(L);
    lua_close(L);
    return 0;
}
