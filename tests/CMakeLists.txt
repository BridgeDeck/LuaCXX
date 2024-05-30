
link_libraries(
    ${PROJECT_NAME}
    ${LUA_LIBRARY}
)

add_executable(Playground Playground.cpp)
add_test(NAME PlaygroundTest COMMAND Playground)

add_executable(get_set_globals get_set_globals/main.cpp)
add_test(NAME "Getting and Setting Globals" COMMAND get_set_globals)