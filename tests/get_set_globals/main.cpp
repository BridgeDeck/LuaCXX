#include "../testing.h"
#include "LuaCXX_Common.hpp"
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
		// test setting threads
		{
			Thread created_engine = lua.new_thread();
			gt.rawset(lua.new_string("engine"), lua.new_thread());

			Thread the_engine = gt.rawget(lua.new_string("engine"));
			ASSERT(the_engine.get_type()==VariantType::THREAD,
				"This engine is not an engine at all!");
		}
		// test setting userdata
		{
			struct Driver{int skills;};
			Userdata<struct Driver> driver = lua.new_userdata<struct Driver>();
			driver->skills = 100;
			gt.rawset(lua.new_string("the_driver"), driver);

			Userdata<struct Driver> selected_driver = gt.rawget(lua.new_string("the_driver"));
			ASSERT(selected_driver->skills==100, 
				"This isnt the driver, the skills are different!");
		}
		//test setting light userdata
		{
			struct Music{double catchiness;};
			struct Music *remote_music_bank= new Music;
			remote_music_bank->catchiness=87.25;
			LightUserdata<struct Music> inserted_music = lua.new_light_userdata(remote_music_bank);
			gt.rawset(lua.new_string("playing_music"), inserted_music);

			LightUserdata<struct Music> playing_music = gt.rawget(lua.new_string("playing_music"));
			ASSERT(playing_music->catchiness > 80.0,
				"What shitty music is this!?");
			
			delete remote_music_bank;
		}
		// test setting functions
		{
			struct f{
				static int useless_feature(lua_State*L)
				{
					lua_pushnumber(L, 250609.0);
					return 0;
				}
			};
			Variant cars_useless_feature = lua.new_function(f::useless_feature);
			gt.rawset(lua.new_string("useless_feature"), cars_useless_feature);

			lua_CFunction showing_useless_feature = gt.rawget(lua.new_string("useless_feature"));
			showing_useless_feature(L);

			ASSERT(lua_tonumber(L, -1)==250609.0, 
				"I know this feature is useless, but can it atleast do something to interest me?");
		}
		// test setting nil
		{
			gt.rawset(lua.new_string("my_car_color"), lua.new_nil());
			ASSERT(gt.rawget(lua.new_string("my_car_color")).get_type()==VariantType::NIL, 
				"Not nil somehow...")
				
			gt.rawset(lua.new_string("has_driver"), lua.new_nil());
			ASSERT(gt.rawget(lua.new_string("has_driver")).get_type()==VariantType::NIL, 
				"Not nil somehow...")

			gt.rawset(lua.new_string("speed"), lua.new_nil());
			ASSERT(gt.rawget(lua.new_string("speed")).get_type()==VariantType::NIL, 
				"Not nil somehow...")

			gt.rawset(lua.new_string("tire_pressure"), lua.new_nil());
			ASSERT(gt.rawget(lua.new_string("tire_pressure")).get_type()==VariantType::NIL, 
				"Not nil somehow...")

			gt.rawset(lua.new_string("engine"), lua.new_nil());
			ASSERT(gt.rawget(lua.new_string("engine")).get_type()==VariantType::NIL, 
				"Not nil somehow...")

			gt.rawset(lua.new_string("the_driver"), lua.new_nil());
			ASSERT(gt.rawget(lua.new_string("the_driver")).get_type()==VariantType::NIL, 
				"Not nil somehow...")

			gt.rawset(lua.new_string("playing_music"), lua.new_nil());
			ASSERT(gt.rawget(lua.new_string("playing_music")).get_type()==VariantType::NIL, 
				"Not nil somehow...")

			gt.rawset(lua.new_string("useless_feature"), lua.new_nil());
			ASSERT(gt.rawget(lua.new_string("useless_feature")).get_type()==VariantType::NIL, 
				"Not nil somehow...")
		}
	}	

	lua_close(L);
	FINISH_TEST;
}
