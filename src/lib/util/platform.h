/**
 * @file:   platform.h
 * @author: Gereon Kremer <gereon.kremer@cs.rwth-aachen.de>
 *
 * This file contains platform and compiler specific macros.
 */

#pragma once

//////////////////////
// Compiler identification
// taken from http://sourceforge.net/p/predef/wiki/Compilers/

#define STRINGIFY(s) #s

#ifdef __clang__
#define __CLANG

#define CLANG_WARNING_DISABLE(warning)\
		_Pragma("clang diagnostic push")\
		_Pragma( STRINGIFY(clang diagnostic ignored warning) )
#define CLANG_WARNING_RESET\
		_Pragma("clang diagnostic pop")
#elif __GNUC__
#define __GCC

	#define CLANG_WARNING_DISABLE(warning)
	#define CLANG_WARNING_RESET
#else
	#warning "You are using an unsupported compiler."
	#define __UNSUPPORTED
#endif