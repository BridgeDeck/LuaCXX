#include "../testing.h"
#include "LuaCXX_Common.hpp"
#include "LuaCXX_Userdata.hpp"
#include "LuaCXX_Variant.hpp"
#include <iostream>
#include <vector>

using namespace LuaCXX;

constexpr double MINDSET_PESSIMIST = 0.0;
constexpr double MINDSET_OPTIMIST = 1.0;
constexpr double MINDSET_REALIST = 2.0;

struct Mindset{
    float optimistic;
    float pessimistic;
    static int check_mindset_state(lua_State* L)
    {
        Lua lua = L;

        LightUserdata<Mindset> mindset = lua[1];

        Variant buffer;

        const double delta = mindset->optimistic - mindset->pessimistic;
        if (delta > 10.0)
        {
            buffer = lua.new_number(MINDSET_OPTIMIST);
        }
        else if (delta < -10.0)
        {
            buffer = lua.new_number(MINDSET_PESSIMIST);
        }
        else
        {
            buffer = lua.new_number(MINDSET_REALIST);
        }

        return lua.return_values(buffer);
    }
};

int main()
{
    INIT_TEST

    lua_State* L = luaL_newstate();
    init_print_function(L);
    {
        Lua lua = L;
        Mindset mindset = Mindset{57.0, 60.0};

        Variant func = lua.new_function(Mindset::check_mindset_state, lua.new_light_userdata(&mindset));

        std::vector<Variant> returns = func.call();

        ASSERT((double)returns[0]==MINDSET_REALIST, "This guys mindset is not realistic man.");
    }
    lua_close(L);

    FINISH_TEST
}