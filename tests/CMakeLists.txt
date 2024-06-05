
link_libraries(
    ${PROJECT_NAME}
    ${LUA_LIBRARY}
)

add_executable(Playground Playground.cpp)
add_test(NAME PlaygroundTest COMMAND Playground)

add_executable(get_set_globals get_set_globals/main.cpp)
add_test(NAME "Getting and Setting Globals" COMMAND get_set_globals)

add_executable(get_set_registry get_set_registry/main.cpp)
add_test(NAME "Getting and Setting Lua's Registry" COMMAND get_set_registry)

add_executable(lib_making lib_making/main.cpp)
add_test(NAME "Creating libraries to use inside Lua" COMMAND lib_making)

add_executable(metatable_userdata metatable_userdata/main.cpp)
add_test(NAME "Creating Userdata's and assigning them metatables" COMMAND metatable_userdata)

add_executable(protected_calls protected_calls/main.cpp)
add_test(NAME "Test out protected calls" COMMAND protected_calls)

add_executable(compile_and_dump compile_and_dump/main.cpp)
add_test(NAME "Testing compiling and dumping Lua chunks" COMMAND compile_and_dump)

add_executable(call_lua_function call_lua_function/main.cpp)
add_test(NAME "Call a function defined in Lua and get its return" COMMAND call_lua_function)

add_executable(iterate_table iterate_table/main.cpp)
add_test(NAME "Iterate through a table" COMMAND iterate_table)

add_executable(function_env function_env/main.cpp)
add_test(NAME "Set the environment of a function" COMMAND function_env)