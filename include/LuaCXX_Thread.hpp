#ifndef LuaCXX_Thread_HPP
#define LuaCXX_Thread_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"
#include "LuaCXX_Lua.hpp"

namespace LuaCXX
{
class Thread: public Variant
{
	friend class Lua;
	private:
	public:
	

	operator lua_State*();
	operator Lua();
	
};
}
#endif