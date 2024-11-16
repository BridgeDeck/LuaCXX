#include "LuaCXX.hpp"
#include "Internal.hpp"
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
    is_state_internal=false;
}

Variant::Variant(lua_State* lua, int index)
{
    // L = luaL_newstate();
    // is_state_internal=true;
    // lua_pushvalue(lua, index);
    // lua_xmove(lua, L, lua_gettop(lua));
    // stack_index=lua_gettop(L);
    L=lua;
    stack_index=index;
    is_state_internal=false;
}

Variant::~Variant()
{
    if (is_state_internal && L!=0)
        lua_close(L);
}

// Variant::Variant(const char* str)
// {
//   L=luaL_newstate();
//   is_state_internal=true;
//   lua_pushstring(L, str);
//   stack_index = lua_gettop(L);
// }

// Variant::Variant(double num)
// {
//   L=luaL_newstate();
//   is_state_internal=true;
//   lua_pushnumber(L, num);
//   stack_index = lua_gettop(L);
// }

// Variant::Variant(bool b)
// {
//   L=luaL_newstate();
//   is_state_internal=true;
//   if (b)
//     lua_pushboolean(L, 1);
//   else
//     lua_pushboolean(L, 0);
//   stack_index = lua_gettop(L);
// }

// Variant::Variant(lua_CFunction func)
// {
//     L=luaL_newstate();
//     is_state_internal=true;
//     lua_pushcclosure(L, func, 0);
//     stack_index=lua_gettop(L);
// }

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
    // lua_pushvalue(L, key.stack_index);
    key.copyvalue_into(L);
    lua_rawget(L, stack_index);
    return Variant(L, lua_gettop(L));
}

void Variant::rawset(Variant key, Variant value)
{
    //key.can_be_nillified = false;
    //value.can_be_nillified = false;
    // DBGF(lua_pushvalue(L, key.stack_index));
    // DBGF(lua_pushvalue(L, value.stack_index));
    key.copyvalue_into(L);
    value.copyvalue_into(L);
    DBGF(lua_rawset(L, stack_index));
}

Variant Variant::get(Variant key)
{
    // lua_pushvalue(L, key.stack_index);
    key.copyvalue_into(L);
    lua_gettable(L, stack_index);
    return Variant(L, lua_gettop(L));
}
void Variant::set(Variant key, Variant value)
{
    // lua_pushvalue(L, key.stack_index);
    // lua_pushvalue(L, value.stack_index);
    key.copyvalue_into(L);
    value.copyvalue_into(L);
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
        i->copyvalue_into(L);
        // lua_pushvalue(L, i->stack_index);
    
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
        i->copyvalue_into(L);
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
        key.copyvalue_into(L);
        // lua_pushvalue(L, key.stack_index);

    
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

void Variant::copyvalue_into(lua_State* into)
{
    if (L == into)
    {
        lua_pushvalue(L, stack_index);
    }
    else 
    {
        lua_pushvalue(L, stack_index);
        lua_xmove(L, into, -1);
    }
}
