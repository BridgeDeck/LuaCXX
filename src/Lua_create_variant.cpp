/*
    This source file is for `Lua`'s methods that create handles to values.
*/
#include "LuaCXX.hpp"
#include "Internal.hpp"
#include "LuaCXX_Common.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace LuaCXX;

String Lua::new_string(const char *my_str)
{
    DBG("String Lua::new_string(const char *my_str)");
    DBGF(lua_pushstring(L, my_str));
    return Variant(L, lua_gettop(L));
}
Variant Lua::new_boolean(bool b)
{
    DBG("Variant Lua::new_boolean(bool b)");
    if (b)
        lua_pushboolean(L, 1);
    else
        lua_pushboolean(L, 0);
    return Variant(L, lua_gettop(L));
}
Variant Lua::new_number(double n)
{
    DBG("Variant Lua::new_number(double n)");
    lua_pushnumber(L, n);
    return Variant(L, lua_gettop(L));
}

Table Lua::new_table()
{
    DBG("Table Lua::new_table()");
    lua_createtable(L, 0, 0);
    return Variant(L, lua_gettop(L));
}

Thread Lua::new_thread()
{
    DBG("Thread Lua::new_thread()");
    lua_newthread(L);
    return Variant(L, lua_gettop(L));
}

Variant Lua::new_function(lua_CFunction f)
{
    DBG("Variant Lua::new_function(lua_CFunction f)");
    Variant func = new_function(f, _tmp_func_binds);
    _tmp_func_binds.clear();
    return func;
}

Variant Lua::new_function(lua_CFunction f, std::vector<Variant> binds)
{
    DBG("Variant Lua::new_function(lua_CFunction f, std::vector<Variant> binds)");

    size_t bind_count = 0;
    for (auto i = binds.begin();i!=binds.end();i++)
    {
        i->copyvalue_into(L);
        bind_count++;
    }

    lua_pushcclosure(L, f, bind_count);

    return Variant(L, lua_gettop(L));
}

Variant Lua::new_nil()
{
    DBG("Variant Lua::new_nil()");
    lua_pushnil(L);
    return Variant(L, lua_gettop(L));
}
Variant Lua::compile(const char *lua_source_code, const char* chunkname)
{
    DBG("Variant Lua::compile(const char *lua_source_code, const char* chunkname)");
    size_t sz=0;
    while(lua_source_code[sz]!=0 &&
        lua_source_code[sz]!=EOF)
        sz++;
    luaL_loadbuffer(L, lua_source_code, sz, chunkname);
    return Variant(L, lua_gettop(L));
}
