#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"
#include "LuaCXX_Table.hpp"

using namespace LuaCXX;

Table Variant::get_environment() const
{
    lua_getfenv(L, stack_index);
    return (Table(L, lua_gettop(L)));
}

void Variant::set_environment(Table &env)
{
    if (env.get_type() != TABLE)
        return;
    // lua_pushvalue(L, env.stack_index);
    env.copyvalue_into(L);
    lua_setfenv(L, stack_index);
}