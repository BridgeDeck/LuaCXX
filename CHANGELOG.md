# LuaCXX changelog
Version : 2.0
Current Date : 05/06/2024

## `tests/`

### Changed files

#### Changed `tests/CMakeLists.txt`
Added a new test, see `tests/function_env/main.cpp`.

### Added files

#### Added `tests/function_env/main.cpp`
A Program file for a test to test out changing a functions environment table.

## `src/`

### Changed files

#### Changed `src/Lua_pseudotables.cpp`
Added a check so that if the current Lua version is not 5.1, `Lua::environment` will return a nil value.

### Added files

#### Added `src/Variant_env.cpp`
A file specifically for containing methods that set and get Variant's environment table.

## `include/`

### Changed files

#### Changed `include/LuaCXX_Lua.hpp`
Made `Lua::environment` non-const.

#### Changed `include/LuaCXX_Table.hpp`
Gave `Table` a new friend, `Variant`.

#### Changed `include/LuaCXX_Variant.hpp`
Added new methods `get_environment` and `set_environment` for getting and setting the environment of a Variant.

### Added files


## Other

### Changed files

#### Changed `CMakeLists.txt`
Added `src/Variant_env.cpp` as a source file

#### Changed `Makefile`
Removed some junk dependencies and fixed an issue where not enough arguments are passed into changelog_gen.lua.

### Added files


