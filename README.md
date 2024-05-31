# LuaCXX

This is a C++ library that makes it easier to use Lua by providing an intuitive abstraction over the Lua state. Allowing you to easily put it into any existing project that integrates Lua.

**This library is still very much in the works, it lacks access to many Lua's most useful features.**

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

## Code Samples

Simply wrap `LuaCXX::Lua` around an existing `lua_State*` and you are ready.
```cpp
lua_State* L = luaL_newstate();
Lua luacxx = Lua(L); // Use LuaCXX from here
```

 Lua's globals, registry and environment tables are available as plain Tables.
 ```cpp
luacxx.globals();
luacxx.environment();
luacxx.registry();
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

