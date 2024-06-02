#include "../testing.h"
#include "LuaCXX_Common.hpp"
#include <iostream>
#include <vector>

using namespace LuaCXX;

int main()
{
    INIT_TEST

    lua_State* L = luaL_newstate();
    init_print_function(L);
    {
        Lua lua = Lua(L);
        Variant chunk = lua.compile(
            //"function cad()"
            "print(\"I was part of a Compile and Dump project.\")"
            //"end"
        );
        std::vector<char> buf;
        chunk.dump(buf);
        std::cout << "Chunk: " << buf.data() << std::endl;

        /*
            TODO: For some reason, when the bytecode gets loaded, it becomes a string in the stack
            and not a function. This needs to be fixed.
        */ 
        Variant new_chunk = lua.compile(buf.data());
        std::vector<Variant> results = new_chunk.call();
        
        //std::cout<<"Result of the above compiled chunk: " << (const char*)(String)(chunk_return[0]) << std::endl;
    }
    lua_close(L);

    FINISH_TEST
}