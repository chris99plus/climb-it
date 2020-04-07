// ***************************************************************************
// monitor - runtime monitoring
// ***************************************************************************

#pragma once
#include "debug.h"
#include "../utils/print.h"

// ---------------------------------------------------------------------------
// monitor(text, var);
// ---------------------------------------------------------------------------

#ifndef NDEBUG
#define monitor(text, expr) \
	if(__builtin_types_compatible_p(typeof(expr), unsigned int)) \
	{ \
        _f_debug(text "\x80", 0, (void (*)(void*)) &print_unsigned_int, &expr, __FILE__, sizeof(__FILE__), __LINE__); \
	} \
	if(__builtin_types_compatible_p(typeof(expr), signed int)) \
	{ \
        _f_debug(text "\x80", 1, (void (*)(void*)) &print_signed_int, &expr, __FILE__, sizeof(__FILE__), __LINE__); \
	} \
	if(__builtin_types_compatible_p(typeof(expr), long unsigned int)) \
	{ \
        _f_debug(text "\x80", 2, (void (*)(void*)) &print_long_unsigned_int, &expr, __FILE__, sizeof(__FILE__), __LINE__); \
 	} \
	if(__builtin_types_compatible_p(typeof(expr), long signed int)) \
	{ \
        _f_debug(text "\x80", 3, (void (*)(void*)) &print_long_signed_int, &expr, __FILE__, sizeof(__FILE__), __LINE__); \
	}
#else
#define monitor(text, expr)
#endif

// ***************************************************************************
// end of file
// ***************************************************************************
