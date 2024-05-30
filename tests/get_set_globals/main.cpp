#include "../testing.h"
#include <cstring>
#include <iostream>
using namespace LuaCXX;

int main()
{	
	lua_State* L = luaL_newstate();
	{
		Lua lua = L;
		Table gt = lua.globals();

		// set the values
		gt.rawset(
			lua.new_string("my_car_color"), 
			lua.new_string("red"));
		ASSERT(strcmp(gt.rawget<const char*, const char*>("my_car_color"), "red"), 
			"My car color is not red?!");
		
	}
	lua_close(L);
	return 0;
}
