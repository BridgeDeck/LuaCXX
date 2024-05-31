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

int _lua_print_func(lua_State* L)
{
    Lua lua = Lua(L);
    Stack stack = lua.stack();
    std::vector<Variant> args = stack.as_array();

    for (auto i = args.begin();i!=args.end();i++)
    {
        switch (i->get_type()) {
            case VariantType::BOOLEAN:
            if ((bool)*i)
                std::cout << true;
            else
                std::cout << false;
            break;
            case VariantType::STRING:
            std::cout << (const char*)(String)*i;
            break;
            case VariantType::NUMBER:
            std::cout << (double)*i;
            break;
            default:
            break;
        }
        std::cout << std::endl;
    }

    return 0;
}

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
        lua.globals()
            .rawset(lua.new_string("print"),
            lua.new_function(_lua_print_func));
        
        Table lib_table = lua.new_table();
        lib_table.rawset(lua.new_string("shoot"), 
            lua.new_function(_lua_human_shoot));
        lib_table.rawset(lua.new_string("sing"), 
            lua.new_function(_lua_human_sing));
        lib_table.rawset(lua.new_string("has_weapon"), 
            lua.new_function(_lua_human_has_weapon));
        
        lua.globals()
            .rawset(lua.new_string("human"), lib_table);

        Variant lua_program = lua.compile(lua_source_code);
        lua_program.call();

    }
    lua_close(L);

    FINISH_TEST
}