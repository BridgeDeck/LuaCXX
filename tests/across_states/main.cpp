#include "../testing.h"
using namespace LuaCXX;
int main()
{
    INIT_TEST
    lua_State* L1 = luaL_newstate();
    lua_State* L2 = luaL_newstate();

    {
        Lua lua1 = Lua(L1);
        Lua lua2 = Lua(L2);
        Table t = lua1.new_table();
        t.set(lua2.new_string("Testfield"), lua2.new_number(1.0));
        ASSERT((double)t.get(lua1.new_string("Testfield"))==1.0, "Testfield is not the proper value");
    }
    lua_close(L1);
    lua_close(L2);

    FINISH_TEST
}