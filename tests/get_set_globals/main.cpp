#include "../testing.h"
#include <cstring>
#include <iostream>
using namespace LuaCXX;
using namespace std;
int main()
{	
	INIT_TEST;
	lua_State* L = luaL_newstate();
	{
		Lua lua = L;
		Table gt = lua.globals();

		// Test setting strings
		{
			String key_my_car_color = lua.new_string("my_car_color");
			String expected_car_color = lua.new_string("red");
			gt.rawset(
				key_my_car_color, 
				expected_car_color);
			ASSERT(
				strcmp(
					(String)gt.rawget(key_my_car_color), 
					expected_car_color) == 0, 
				"The car color is not red?!");
		}
		// Test setting booleans
		{
			gt.rawset(
				lua.new_string("has_driver"), 
				lua.new_boolean(false));
			ASSERT((bool)gt.rawget(lua.new_string("has_driver")) == false, 
				"Hey! There is a thief in the car!");
		}
		// test setting numbers
		{
			gt.rawset(
				lua.new_string("speed"), 
				lua.new_number(80.0)
			);
			ASSERT((double)gt.rawget(lua.new_string("speed")) == 80.0, 
				"This car's speed seems off...");
		}
		// test setting tables
		{
			Table tire_pressure = lua.new_table();
			
			tire_pressure.rawset(
				lua.new_string("tire_1"), 
				lua.new_number(60.0));
			tire_pressure.rawset(
				lua.new_string("tire_2"), 
				lua.new_number(59.2));
			tire_pressure.rawset(
				lua.new_string("tire_3"), 
				lua.new_number(63.2));
			tire_pressure.rawset(
				lua.new_string("tire_4"), 
				lua.new_number(63.7));
			
			gt.rawset(lua.new_string("tire_pressure"), tire_pressure);

			Table results = gt.rawget(lua.new_string("tire_pressure"));

			// utility function for if a tire is up to code
			struct inspector{
				static bool up_to_code(double pressure)
				{
					return (pressure < 65.0 && pressure > 55.0);
				}
			};

			ASSERT(inspector::up_to_code((double)results.rawget(lua.new_string("tire_1")))
				&& inspector::up_to_code((double)results.rawget(lua.new_string("tire_2")))
				&& inspector::up_to_code((double)results.rawget(lua.new_string("tire_3")))
				&& inspector::up_to_code((double)results.rawget(lua.new_string("tire_4"))), 
				"Some of these tires are not up to code...");
		}
	}
	lua_close(L);
	FINISH_TEST;
}
