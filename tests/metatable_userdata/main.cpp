#include "../testing.h"
#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"
#include <cstring>
#include <vector>

using namespace LuaCXX;

class Component
{
    public:
    Component(const char* display)
    {
        to_display = display;
    }

    static void init_metatable(Userdata<Component> comp)
    {
        Lua lua = Lua(comp.get_lua());
        Table t = lua.new_table();
        t.rawset(lua.new_string("__index"), 
            lua.new_function(__index));
        comp.set_metatable(t);
    }
    private:
    static int __index(lua_State* L)
    {
        Lua lua = Lua(L);
        Userdata<Component> comp = lua.stack()[1];
        
        std::vector<Variant> r = {} ;
        if (strcmp((String)lua.stack()[2], "to_display")==0)
            r.push_back(lua.new_string(comp->to_display));
        else
            r.push_back(lua.new_nil());

        return lua.stack()._return(r);
    }
    const char* to_display;
};

int main()
{

    INIT_TEST
    lua_State* L = luaL_newstate();
    {
        Lua lua = Lua(L);
        init_print_function(lua);

        Userdata<Component> comp = lua.new_userdata<Component>("Hello World!");
        Component::init_metatable(comp);
        lua.globals()
            .rawset(lua.new_string("ext_component"), comp);
        lua.compile(
            "print(ext_platform.to_display)\n"
        );
    }
    lua_close(L);
    FINISH_TEST
}