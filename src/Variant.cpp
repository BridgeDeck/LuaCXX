#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"
#include <vector>

using namespace LuaCXX;

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
    if (get_type()!=VariantType::FUNCTION)
        return {};
    
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
    if (get_type()!=VariantType::FUNCTION)
        return {};
    
    std::vector<Variant> r = {};
    lua_pushvalue(L, stack_index);
    int results = lua_gettop(L);

    for (auto i = args.begin();i!=args.end();i++)
        lua_pushvalue(L, i->stack_index);
    
    error_code_out = lua_pcall(L, args.size(), LUA_MULTRET, errhandler.stack_index);
    while (lua_type(L, results)!=LUA_TNONE)
    {
        r.push_back(Variant(L, results));
        results++;
    }
    return r;
}
lua_State* Variant::get_lua() const
{
    return L;
}