
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