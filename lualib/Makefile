LUA_MAKEFLAGS=
LUAJIT_MAKEFLAGS=

# Lua 5.1
lua-5.1.4.tar.gz:
	curl -O https://lua.org/ftp/lua-5.1.4.tar.gz
lua-5.1.4/: lua-5.1.4.tar.gz
	tar -xf lua-5.1.4.tar.gz
lua-5.1.4/src/liblua.a: lua-5.1.4/ ${LUA_MAKEFLAGS}
	cd lua-5.1.4/src && $(MAKE) ansi ${LUA_MAKEFLAGS}
LUA51: lua-5.1.4/src/liblua.a

# Lua 5.2
lua-5.2.4.tar.gz:
	curl -O https://lua.org/ftp/lua-5.2.4.tar.gz
lua-5.2.4/: lua-5.2.4.tar.gz
	tar -xf lua-5.2.4.tar.gz
lua-5.2.4/src/liblua.a: lua-5.2.4/
	cd lua-5.2.4/src && $(MAKE) ansi ${LUA_MAKEFLAGS}
LUA52: lua-5.2.4/src/liblua.a

# Lua 5.3
lua-5.3.6.tar.gz:
	curl -O https://lua.org/ftp/lua-5.3.6.tar.gz
lua-5.3.6/: lua-5.3.6.tar.gz
	tar -xf lua-5.3.6.tar.gz
lua-5.3.6/src/liblua.a: lua-5.3.6/ ${LUA_MAKEFLAGS}
	cd lua-5.3.6/src && $(MAKE) c89 ${LUA_MAKEFLAGS}
LUA53: lua-5.3.6/src/liblua.a

# Lua 5.4
lua-5.4.6.tar.gz:
	curl -O https://lua.org/ftp/lua-5.4.6.tar.gz
lua-5.4.6/: lua-5.4.6.tar.gz
	tar -xf lua-5.4.6.tar.gz
lua-5.4.6/src/liblua.a: lua-5.4.6/ ${LUA_MAKEFLAGS}
	cd lua-5.4.6/src && $(MAKE) c89 ${LUA_MAKEFLAGS}
LUA54: lua-5.4.6/src/liblua.a

# LuaJIT 2.0
luajit2.0/:
	git clone --branch v2.0 -- https://github.com/LuaJIT/LuaJIT.git luajit2.0
luajit2.0/src/libluajit.a: luajit2.0/
	cd luajit2.0/src/ && $(MAKE) 
LUAJIT20: luajit2.0/src/libluajit.a

# LuaJIT 2.1
luajit2.1/:
	git clone --branch v2.1 -- https://github.com/LuaJIT/LuaJIT.git luajit2.1
luajit2.1/src/libluajit.a: luajit2.1/
	cd luajit2.1/src/ && $(MAKE) 
LUAJIT21: luajit2.1/src/libluajit.a

.PHONY: LUA51 LUA52 LUA53 LUA54 LUAJIT20 LUAJIT21 ${LUA_MAKEFLAGS} ${LUAJIT_MAKEFLAGS}