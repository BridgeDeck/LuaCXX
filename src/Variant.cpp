#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace LuaCXX;

Variant::Variant()
{
    L=0;
    stack_index=0;
}

Variant::Variant(lua_State* lua, int index)
{
    stack_index = index;
    L = lua;
}

VariantType Variant::get_type() const
{
    VariantType r = VariantType::NIL;
    switch (lua_type(L, stack_index)) {
        case LUA_TNONE:
        r = NONE;
        break;
        case LUA_TNIL:
        r=NIL;
        break;
        case LUA_TBOOLEAN:
        r=BOOLEAN;
        break;
        case LUA_TLIGHTUSERDATA:
        r=LIGHTUSERDATA;
        break;
        case LUA_TNUMBER:
        r=NUMBER;
        break;
        case LUA_TSTRING:
        r=STRING;
        break;
        case LUA_TTABLE:
        r=TABLE;
        break;
        case LUA_TFUNCTION:
        r=FUNCTION;
        break;
        case LUA_TUSERDATA:
        r=USERDATA;
        break;
        case LUA_TTHREAD:
        r=THREAD;
        break;
    }
    return r;
}

Variant Variant::rawget(Variant key) const
{
    //key.can_be_nillified = false;
    lua_pushvalue(L, key.stack_index);
    lua_rawget(L, stack_index);
    return Variant(L, lua_gettop(L));
}

void Variant::rawset(Variant key, Variant value)
{
    //key.can_be_nillified = false;
    //value.can_be_nillified = false;
    lua_pushvalue(L, key.stack_index);
    lua_pushvalue(L, value.stack_index);
    lua_rawset(L, stack_index);
}

Variant Variant::get(Variant key)
{
    lua_pushvalue(L, key.stack_index);
    lua_gettable(L, stack_index);
    return Variant(L, lua_gettop(L));
}
void Variant::set(Variant key, Variant value)
{
    lua_pushvalue(L, key.stack_index);
    lua_pushvalue(L, value.stack_index);
    lua_settable(L, stack_index);
}

std::vector<Variant> Variant::call()
{
    std::vector<Variant> r = call(_tmp_args);
    _tmp_args={};
    return r;
}

std::vector<Variant> Variant::call(std::vector<Variant> args)
{
    
    std::vector<Variant> r = {};
    lua_pushvalue(L, stack_index);
    int results = lua_gettop(L);

    for (auto i = args.begin();i!=args.end();i++)
        lua_pushvalue(L, i->stack_index);
    
    lua_call(L, args.size(), LUA_MULTRET);
    while (lua_type(L, results)!=LUA_TNONE)
    {
        r.push_back(Variant(L, results));
        results++;
    }
    return r;
}
std::vector<Variant> Variant::pcall(Variant errhandler, int& error_code_out)
{
    std::vector<Variant> r = pcall(errhandler, error_code_out, _tmp_args);
    _tmp_args={};
    return r;
}

std::vector<Variant> Variant::pcall(Variant errhandler, int& error_code_out, std::vector<Variant> args)
{
    
    std::vector<Variant> r = {};
    lua_pushvalue(L, stack_index);
    int results = lua_gettop(L);

    for (auto i = args.begin();i!=args.end();i++)
        lua_pushvalue(L, i->stack_index);
    int hfunc_index = errhandler.stack_index;
    if (errhandler.get_type()!=VariantType::FUNCTION)
        hfunc_index=0;
    error_code_out = lua_pcall(L, args.size(), LUA_MULTRET, hfunc_index);
    while (lua_type(L, results)!=LUA_TNONE)
    {
        r.push_back(Variant(L, results));
        results++;
    }
    return r;
}

int _dump_writer(lua_State*L, const void* chunk, size_t sz, void* ud)
{
    std::vector<char>* into = (std::vector<char>*)ud;

    for (size_t i=0;i<sz;i++)
        into->push_back(((const char*)chunk)[i]);

    return 0;
}
void Variant::dump(std::vector<char>& into)
{
    lua_dump(L, _dump_writer, &into);
}

bool Variant::next(Variant& key, Variant& value)
{
    if (!key.L)
        key.L = L;
    if (!value.L)
        value.L = L;

    if (value.stack_index == lua_gettop(L))
        lua_pop(L, 1);
    if (key.stack_index==0)
        lua_pushnil(L);
    else if (key.stack_index < lua_gettop(L))
        lua_pushvalue(L, key.stack_index);

    
    int r = lua_next(L, stack_index);

    key.stack_index = lua_gettop(L)-1;
    value.stack_index = lua_gettop(L);

    if (r==0)
        return false;
    else
        return true;
}

lua_State* Variant::get_lua() const
{
    return L;
}