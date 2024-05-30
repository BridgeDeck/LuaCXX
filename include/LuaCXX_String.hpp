#ifndef LuaCXX_String_HPP
#define LuaCXX_String_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"

namespace LuaCXX
{
/*
    Handle to a string
*/
class String:public Variant
{
    public:
    operator const char*();
};
}

#endif