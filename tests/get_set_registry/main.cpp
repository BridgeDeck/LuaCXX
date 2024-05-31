#include "../testing.h"
#include <cstring>

using namespace LuaCXX;

// Use this as a key for accessing an internal value in the registry
const char key = 'k';

int main()
{
    INIT_TEST

    lua_State* L = luaL_newstate();

    {
        Lua lua = Lua(L);
        Table rt = lua.registry();

        rt.rawset(lua.new_light_userdata(&key), lua.new_string("Hello World"));

        ASSERT(strcmp((String)rt.rawget(lua.new_light_userdata(&key)), "Hello World")==0,
            "Hey! Say hello to the world now!")
    }

    lua_close(L);
    FINISH_TEST
}