#ifndef LuaCXX_MetaObject_HPP
#define LuaCXX_MetaObject_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"

namespace LuaCXX
{
class MetaObject
{
    public:
	int (*__index)(lua_State*);
	int (*__set_index)(lua_State*);
    protected:
};
}
#endif
