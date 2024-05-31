cmake_minimum_required(VERSION 3.28)
project(LuaCXX)

set(DEFAULT_LUA_INCLUDE_DIR "/usr/include")
set(DEFAULT_LUA_LIBRARY "/usr/lib/liblua.a")

if(NOT DEFINED LUA_INCLUDE_DIR)
	message(WARNING "LUA_INCLUDE_DIR not specified, defaulting to ${DEFAULT_LUA_INCLUDE_DIR}")
	set(LUA_INCLUDE_DIR ${DEFAULT_LUA_INCLUDE_DIR})
endif()
if(NOT DEFINED LUA_LIBRARY)
	message(WARNING "LUA_LIBRARY not specified, defaulting to ${DEFAULT_LUA_LIBRARY}")
	set(LUA_LIBRARY ${DEFAULT_LUA_LIBRARY})
endif()

# C++11
set(CMAKE_CXX_STANDARD 11)

set (SRC_FILES
	src/Thread.cpp
	src/Table.cpp
	src/String.cpp
	src/Stack.cpp
	src/Variant.cpp
	src/Variant_conversion.cpp
	src/Lua.cpp
	src/Lua_pseudotables.cpp
	src/Lua_create_variant.cpp
)

set (INC_FILES
	include/LuaCXX.hpp
	include/LuaCXX_Common.hpp
	include/LuaCXX_Thread.hpp
	include/LuaCXX_Table.hpp
)

include_directories(${LUA_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

include(CTest)
add_subdirectory(tests)
