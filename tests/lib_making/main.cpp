#include "../testing.h"
#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"
#include <iostream>
#include <ostream>
#include <vector>
using namespace LuaCXX;

const char* lua_source_code=
"print(human.shoot())\n"
"print(human.sing())\n"
"if human.has_weapon() then\n"
"   print(\"Embrace the darkness thats within me!\")\n"
"end\n";



int _lua_human_shoot(lua_State*L)
{
    Lua lua = Lua(L);
    return lua.stack()._return(lua.new_string("Bang Bang Bang!"));
}

int _lua_human_sing(lua_State* L)
{
    Lua lua = Lua(L);
    return lua.stack()._return(lua.new_string("Pull my devil trigger!"));
}
int _lua_human_has_weapon(lua_State* L)
{
    Lua lua = Lua(L);
    return lua.stack()._return(lua.new_boolean(true));
}
int main()
{
    INIT_TEST

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    {
        Lua lua = Lua(L);
        init_print_function(lua);
        
        Table lib_table = lua.new_table();
        lib_table.rawset(lua.new_string("shoot"), 
            lua.new_function(_lua_human_shoot));
        lib_table.rawset(lua.new_string("sing"), 
            lua.new_function(_lua_human_sing));
        lib_table.rawset(lua.new_string("has_weapon"), 
            lua.new_function(_lua_human_has_weapon));
        
        lua.globals()
            .rawset(lua.new_string("human"), lib_table);

        Variant lua_program = lua.compile(lua_source_code, "Library Creation Test");
        lua_program.call();

    }
    lua_close(L);

    FINISH_TEST
}