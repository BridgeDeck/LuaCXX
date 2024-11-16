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
	# src/Stack.cpp
	src/Variant.cpp
	src/Variant_env.cpp
	src/Variant_metatable.cpp
	src/Variant_conversion.cpp
	src/Lua.cpp
	src/Lua_pseudotables.cpp
	src/Lua_create_variant.cpp
)

set (INC_FILES
	include/LuaCXX_Common.hpp
	include/LuaCXX_Lua.hpp
	# include/LuaCXX_Stack.hpp
	include/LuaCXX_String.hpp
	include/LuaCXX_Table.hpp
	include/LuaCXX_Thread.hpp
	include/LuaCXX_Userdata.hpp
	include/LuaCXX_Variant.hpp
	include/LuaCXX_Version.hpp
	include/LuaCXX.hpp
)

include_directories(${LUA_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

if (${VERBOSE_DEBUG_PRINTING})
add_compile_definitions(VERBOSE_DEBUG_PRINTING)
endif()
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})

include(CTest)
add_subdirectory(tests)

install(TARGETS ${PROJECT_NAME} DESTINATION lib/)
install(FILES ${INC_FILES} DESTINATION include/)
if (IS_DIRECTORY ${PROJECT_SOURCE_DIR}/docs/)
	install(DIRECTORY docs/ DESTINATION .)
endif()
