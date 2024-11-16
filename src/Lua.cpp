#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"
#include <cstddef>
#include <mutex>
#include <vector>

using namespace LuaCXX;

Lua::Lua(lua_State*lua)
{
    L=lua;
}

ThreadStatus Lua::get_status()const
{
    ThreadStatus r = ThreadStatus::Ended;
    switch (lua_status(L)) {
        case LUA_YIELD:
        r=ThreadStatus::Yield;
        break;
        case 0:
        r=ThreadStatus::Ended;
        break;
        default:
        r=ThreadStatus::Error;
        break;
    }
    return r;
}

// Stack Lua::stack() const
// {
//     return Stack(L);
// }

Variant Lua::operator[](size_t index) const
{
    return Variant(L, index);
}

std::vector<Variant> Lua::get_stack_as_array() const
{
    std::vector<Variant> v_vec = {};

    int index_b = 1;

    while (lua_type(L, index_b) != LUA_TNONE)
    {
        index_b++;
        v_vec.push_back(Variant(L, index_b));
    }

    return v_vec;
}

Lua::operator lua_State *()
{
    return L;
}

int Lua::return_values()
{
    int rint = return_values(_tmp_return_values);
    _tmp_return_values.clear();
    return rint;
}

int Lua::return_values(std::vector<Variant> return_values)
{
    int rint = 0;
    for (auto i = return_values.begin();i!=return_values.end();i++)
    {
        lua_pushvalue(L, i->stack_index);
        rint++;
    }
    return rint;
}