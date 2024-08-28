#ifndef LUACXX_Internal_HPP
#define LUACXX_Internal_HPP
#include <iostream>
#include <ostream>
#ifdef VERBOSE_DEBUG_PRINTING
#define DBG(message) \
    std::cout << __FILE__ << ":" << __LINE__ << "| " << message << std::endl;
#define DBGF(func) \
    std::cout << __FILE__ << ":" << __LINE__ << "| " << #func << std::endl; \
    func;
#else
#define DBG(message)
#define DBGf(func)
#endif
#endif