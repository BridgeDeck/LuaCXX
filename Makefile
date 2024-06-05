# This is a utility Makefile to make it simpler to build and test

INCLUA=/usr/include
LIBLUA=/usr/lib/liblua.a
BINLUA=/usr/bin/lua

INSTALL_PREFIX=${PWD}/local

PROJECT_MAJ=2
PROJECT_MIN=1
PROJECT_VERFILE=include/LuaCXX_Version.hpp

CHANGELOG=CHANGELOG.md

CTEST=/usr/bin/ctest
CTEST_FLAGS=-V
CMAKE=/usr/bin/cmake
CMAKE_BUILD_TYPE=Debug
CMAKE_GENERATOR=Ninja
CMAKE_GENFLAGS=
CMAKE_BUILDFLAGS=
CMAKE_C_COMPILER=/usr/bin/gcc
CMAKE_CXX_COMPILER=/usr/bin/g++
CMAKE_BIN=build/

DOXYGEN=/usr/bin/doxygen
DOXYGEN_OVERRIDES=PROJECT_NUMBER=${PROJECT_MAJ}.${PROJECT_MIN}
DOCS_DIR=docs/

default: test build

build: ${INCLUA} ${CMAKE_BUILDFLAGS} ${CMAKE_BIN} ${CMAKE}
	${CMAKE} --build ${CMAKE_BIN} ${CMAKE_BUILDFLAGS}

test: build ${LIBLUA} ${CTEST} ${CTEST_FLAGS}
	cd ${CMAKE_BIN} && ${CTEST} ${CTEST_FLAGS}

install: ${CMAKE_BIN} build ${CMAKE}
	${CMAKE} --install ${CMAKE_BIN} --prefix ${INSTALL_PREFIX}

docs: ${DOCS_DIR}

changelog: ${CHANGELOG}

clean:
	rm -rf ${CMAKE_BIN}
	rm -rf ${DOCS_DIR}

.PHONY: default test build docs changelog \
	${CMAKE_GENFLAGS} ${CMAKE_GENERATOR} ${CMAKE_BUILDFLAGS} ${CMAKE_BUILD_TYPE} \
	${DOXYGEN_OVERRIDES} ${CTEST_FLAGS} ${PROJECT_MAJ} ${PROJECT_MIN}

${DOCS_DIR}: include/*.hpp Doxyfile ${DOXYGEN_OVERRIDES} README.md
	( cat Doxyfile ; echo "${DOXYGEN_OVERRIDES}") | doxygen -

${CMAKE_BIN}: ${CMAKE_GENFLAGS} ${INCLUA} ${LIBLUA} \
	${CMAKE_GENERATOR} ${CMAKE_BUILD_TYPE} ${CMAKE} \
	${CMAKE_C_COMPILER} ${CMAKE_CXX_COMPILER}
	${CMAKE} -S . -B ${CMAKE_BIN} -G${CMAKE_GENERATOR} \
		-D LUA_INCLUDE_DIR="${INCLUA}" \
		-D LUA_LIBRARY="${LIBLUA}" \
		-D CMAKE_C_COMPILER=${CMAKE_C_COMPILER} \
		-D CMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} \
		-D CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} \
		${CMAKE_GENFLAGS}

${CHANGELOG}: ${BINLUA} ${PROJECT_MAJ} ${PROJECT_MIN}
	${BINLUA} changelog_gen.lua ${PROJECT_MAJ}.${PROJECT_MIN} "`date +"%d/%m/%Y"`"