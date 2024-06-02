#include "../testing.h"
#include "LuaCXX_Common.hpp"
#include <vector>

using namespace LuaCXX;

int main()
{
    INIT_TEST

    lua_State* L = luaL_newstate();

    {
        Lua lua = Lua(L);
        std::vector<Variant> returns = lua.compile(
            "return function()\n"
            "   return \"Fulfill our duty, then garbage collected without a trace!\""
            "end\n"
        ).call();

        std::vector<Variant> lfunc_return = returns[0].call();

        ASSERT(lfunc_return[0].get_type()==VariantType::STRING, 
            "Invisible Variant");
    }

    lua_close(L);
    FINISH_TEST
}