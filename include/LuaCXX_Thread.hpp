#ifndef LuaCXX_Thread_HPP
#define LuaCXX_Thread_HPP

#include "LuaCXX_Common.hpp"
#include "LuaCXX_Variant.hpp"

namespace LuaCXX
{
class Thread: public Variant
{
	friend class Lua;
	private:
	public:
	enum Status
	{
		Yield,
		Ended,
		Error
	};
	enum Status get_status() const;

	
};
}
#endif
