# LuaCXX

This is a C++ library that makes it easier to use Lua by providing an intuitive abstraction over the Lua state. Allowing you to easily put it into any existing project that integrates Lua.


## Does it work on version *?

|Version       |Linux    |Windows  |OSX      |
|--------------|---------|---------|---------|
|Lua 5.1.*     |Unknown  |Unknown  |Unknown  |
|Lua 5.2.*     |Unknown  |Unknown  |Unknown  |
|Lua 5.3.*     |Unknown  |Unknown  |Unknown  |
|Lua 5.4.*     |Unknown  |Unknown  |Unknown  |
|LuaJIT 2.0    |Unknown  |Unknown  |Unknown  |
|LuaJIT 2.1    |Yes      |Unknown  |Unknown  |

Feel free to add more Lua versions and platforms Lua is available on to the above table, aswell as testing them out to see if LuaCXX works there or not.
## Building
This library does not need a prebuilt Lua library, only Lua header files.
The Lua library is only needed for building and running tests.

To build it does require CMake 3.28+ and the C++11 standard, both of which should not be too difficult to set up.

### Including in a CMake Project
Set the `LUA_INCLUDE_DIR` option to a directory containing Lua headers.
```cmake
set(LUA_INCLUDE_DIR "/my/path/to/lua/include")
add_subdirectory(LuaCXX)
# Do something with LuaCXX
```

### Linux

Build LuaCXX using the utility Makefile in the root.
```
make build INCLUA=/path/to/lua/include
```

If you want to optimize it for release.
```
make build CMAKE_BUILD_TYPE=Release INCLUA=/path/to/lua/include
```

The utility Makefile chooses Ninja by default to generate build files, to choose something else, set the CMAKE_GENERATOR variable.
```
make build CMAKE_GENERATOR="Unix Makefiles"
```

### Building documentation with Doxygen

The utility Makefile also has a command to build the documentation using doxygen.

```
make docs
```

Use something like Python's `http.server` module to serve the files and view them.
```
cd docs/html
python -m http.server
```


## Code Samples

Simply wrap `LuaCXX::Lua` around an existing `lua_State*` and you are ready.
```cpp
using namespace LuaCXX; // All LuaCXX classes are wrapped in this namespace

lua_State* L = luaL_newstate();
Lua luacxx = Lua(L); // Use LuaCXX from here
```

Lua's globals and registry tables are available as plain Tables.
```cpp
luacxx.globals();
luacxx.registry();
```

Compile Lua source code and run it. (in protected mode)
```cpp
int err;
luacxx.compile("print(\"Hello World!\")", "My Lua Code").pcall(luacxx.new_nil(), err); 
```

Create a table and set its properties
```cpp
Table Player = luacxx.new_table();

// We are working to make it less ugly

// set properties using Variant::set
Player.set(luacxx.new_string("Health"), luacxx.new_number(175.0));

// set properties without invoking metamethods using Variant::rawset
Player.rawset(luacxx.new_string("CurrentWeapon"), luacxx.new_string("The Eyelander")); 

// get properties using Variant::get
Player.get(luacxx.new_string("Health"));

// get properties without invoking metamethods using Variant::rawget
Player.rawget(luacxx.new_string("CurrentWeapon"))
```

Iterate through the contents of a table.
```cpp
Variant key;
Variant value;

while(Player.next(key, value))
{
    // Do something with `key` or `value`
}
```

Create a metatable and assign it to the above table
```cpp
// a table that will become a metatable
Table mt = luacxx.new_table();

// give it a __index metamethod. Replace YOUR_FUNCTION with a valid c function
mt.rawset(luacxx.new_string("__index"), luacxx.new_function(YOUR_FUNCTION));

// give it a __newindex metamethod. Replace YOUR_FUNCTION with a valid c function
mt.rawset(luacxx.new_string("__newindex"), luacxx.new_function(YOUR_FUNCTION));

// Assign the Player table this metatable.
Player.set_metatable(mt);
```

Use `Stack` to read arguments easier.
```cpp

using namespace LuaCXX;

class Game
{
    public:
    int blu_points;
    int red_points;
}

/*
    Suppose this is a global Lua function that takes the parameters `game` and `team`
    `game` is a Userdata that points to an instance of the `Game` class above.
    `team` is a string.
*/
int _get_team_points(lua_State* L)
{
    Lua luacxx = Lua(L); // To use LuaCXX
    
    // Used to access the stack, which contains the arguments to this function
    Stack stack = luacxx.stack(); 

    Userdata<Game> game = stack[1]; // First argument
    String team = stack[2]; // Second argument

    // `String` converts to a `const char*` automatically.
    if (strcmp(team, "red")==0)
        return stack._return(luacxx.new_number(Game->red_points)); // Returns Game::red_points
    else if (strcmp(team, "blu")==0)
        return stack._return(luacxx.new_number(Game->blu_points)); // Returns Game::blu_points
    else
        return stack._return(luacxx.new_nil()); // Returns a nil
}
```

