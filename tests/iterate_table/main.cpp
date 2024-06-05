#include "../testing.h"
#include "LuaCXX_Common.hpp"
#include <cstring>

using namespace LuaCXX;

int main()
{
    INIT_TEST

    lua_State* L = luaL_newstate();
    {
        Lua lua = Lua(L);

        // Test number indices
        {
            Table plot = lua.new_table();

            plot.set(lua.new_number(1.0), lua.new_string("AWAKENING"));
            plot.set(lua.new_number(2.0), lua.new_string("REVENGE"));
            plot.set(lua.new_number(3.0), lua.new_string("RACE"));

            double key_tester = 1.0;

            Variant key;
            Variant value;
            while (plot.next(key, value))
            {
                std::cout << "Chapter " << (double)key << " : " << (const char*)(String)value << std::endl;
                ASSERT((double)key==key_tester, "These chapters are not ordered correctly!");
                key_tester+=1.0;
            }
        }

        // Test string indices
        {
            Table dictionary = lua.new_table();

            const char* key_testset[] = {
                "A",
                "B",
                "C",
                "D",
                "E"
            };

            dictionary.set(lua.new_string(key_testset[0]), lua.new_string("Air"));
            dictionary.set(lua.new_string(key_testset[1]), lua.new_string("Bee"));
            dictionary.set(lua.new_string(key_testset[2]), lua.new_string("Car"));
            dictionary.set(lua.new_string(key_testset[3]), lua.new_string("Dollar"));
            dictionary.set(lua.new_string(key_testset[4]), lua.new_string("Electric"));

            int key_tester=0;
            Variant key;
            Variant value;

            while(dictionary.next(key, value))
            {
                std::cout << (const char*)(String)key << " : " << (const char*)(String)value << std::endl;
                key_tester+=1;
            }
        }


    }
    lua_close(L);

    FINISH_TEST
}