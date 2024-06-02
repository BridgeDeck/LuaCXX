#include "../testing.h"

using namespace LuaCXX;

bool something_went_wrong=false;
int _errhandler(lua_State*L)
{
    Lua lua = Lua(L);
    std::vector<Variant> args = lua.stack().as_array();
    std::cout << (const char*)(String)args[0]<< std::endl;
    something_went_wrong=true;
    return 0;
}

int main()
{
    INIT_TEST

    lua_State* L = luaL_newstate();
    
    {
        Lua lua = Lua(L);

        int err_code;
        lua.compile("totally_legit_class.property()", "Error Testing")
            .pcall(lua.new_function(_errhandler), err_code);
        ASSERT(something_went_wrong, 
            "Something is supposed to go wrong, thats the point!");
        ASSERT(err_code==2, 
            "This error is not as expected");
    }

    lua_close(L);

    FINISH_TEST
}