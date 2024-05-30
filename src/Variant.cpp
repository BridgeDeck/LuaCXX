#include "LuaCXX.hpp"
#include "LuaCXX_Common.hpp"

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