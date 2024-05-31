#ifndef LuaCXX_Stack_HPP
#define LuaCXX_Stack_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"
#include <vector>
namespace LuaCXX
{

class Stack
{
    friend class Lua;
    private:
    Stack(lua_State* lua);
    public:
    Variant operator[](int index) const;

    std::vector<Variant> as_array() const;

    /*
        To be used at the `return` of a Lua CFunction
    */ 
    int _return(std::vector<Variant> return_values);

    /*
        To be used at the `return` of a Lua CFunction
    */
    template<class... ReturnValues>
    int _return(Variant v, ReturnValues... vv)
    {
        _tmp_return_values.push_back(v);
        return _return(vv...);
    }

    /*
        To be used at the `return` of a Lua CFunction
    */
    int _return();

    private:
    std::vector<Variant> _tmp_return_values = {};
    lua_State* L;
};

}

#endif