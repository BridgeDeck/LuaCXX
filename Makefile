# This is a utility Makefile to make it simpler to build and test

INCLUA=/usr/include
LIBLUA=/usr/lib/liblua.a

CTEST=/usr/bin/ctest
CMAKE=/usr/bin/cmake
CMAKE_GENERATOR=Ninja
CMAKE_GENFLAGS=
CMAKE_BUILDFLAGS=
CMAKE_C_COMPILER=/usr/bin/gcc
CMAKE_CXX_COMPILER=/usr/bin/g++
CMAKE_BIN=build/

default: test build

build: ${INCLUA} ${CMAKE_BUILDFLAGS} ${CMAKE_BIN}
	${CMAKE} --build ${CMAKE_BIN} ${CMAKE_BUILDFLAGS}

test: build ${LIBLUA}
	cd ${CMAKE_BIN} && ${CTEST}

.PHONY: default test build ${CMAKE_GENFLAGS} ${CMAKE_GENERATOR} ${CMAKE_BUILDFLAGS}

${CMAKE_BIN}: ${CMAKE_GENFLAGS} ${INCLUA} ${LIBLUA} ${CMAKE_GENERATOR}
	${CMAKE} -S . -B ${CMAKE_BIN} -G${CMAKE_GENERATOR} \
		-D LUA_INCLUDE_DIR="${INCLUA}" \
		-D LUA_LIBRARY="${LIBLUA}" \
		-D CMAKE_C_COMPILER=${CMAKE_C_COMPILER} \
		-D CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} \
		${CMAKE_GENFLAGS}