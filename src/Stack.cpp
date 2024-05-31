#include "LuaCXX_Stack.hpp"
#include "LuaCXX_Variant.hpp"
#include <vector>
using namespace LuaCXX;

Stack::Stack(lua_State *lua)
{
    L=lua;
}

Variant Stack::operator[](int index) const
{
    return Variant(L, index);
}

std::vector<Variant> Stack::as_array() const
{
    int idx_v = 1;
    std::vector<Variant> rv = {};
    while(lua_type(L, idx_v) != LUA_TNONE)
    {
        rv.push_back(Variant(L, idx_v));
        idx_v++;
    }
    return rv;
}

int Stack::_return()
{
    int rint = _return(_tmp_return_values);
    _tmp_return_values.clear();
    return rint;
}

int Stack::_return(std::vector<Variant> return_values)
{
    int rint = 0;
    for (auto i = return_values.begin();i!=return_values.end();i++)
    {
        lua_pushvalue(L, i->stack_index);
        rint++;
    }
    return rint;
}