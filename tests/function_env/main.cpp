#include "../testing.h"

using namespace LuaCXX;
using namespace std;

int main()
{
    INIT_TEST

    lua_State* L = luaL_newstate();
    init_print_function(L);
    {
        Lua lua = Lua(L);

        Variant f = lua.compile("print(environment_var)");
        Table env = lua.new_table();
        env.rawset(lua.new_string("environment_var"), lua.new_string("Hello World!"));

        // Set this metatable so that global functions are still available
        Table env_mt = lua.new_table();
        env_mt.rawset(lua.new_string("__index"), lua.globals());
        env.set_metatable(env_mt);

        f.set_environment(env);
        f.call();
    }
    lua_close(L);

    FINISH_TEST
}