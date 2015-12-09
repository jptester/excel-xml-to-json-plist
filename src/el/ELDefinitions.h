/*
 * definitions.h
 *
 *  Created on: 01/08/2015
 *      Author: Juan Pablo Eguiguren
 *
 *  Data structure specific layer - multipurpose layer
 *
 */

#ifndef ELDEFINITIONS_H_
#define ELDEFINITIONS_H_

#include <string>

#if defined(WIN32) || defined(WINDOWS)
#	include <time.h>
#endif

// Chars
typedef char 			el_char;
#ifdef __cplusplus
#	if __cplusplus >= 201103L
		typedef char16_t		el_char16_t;
		typedef char32_t		el_char32_t;
#	endif
#endif
typedef wchar_t			el_wchar_t;
typedef signed char		el_signed_char;
typedef unsigned char	el_unsigned_char;

// Signed integers
typedef signed short int		el_signed_short_int;
typedef signed int				el_signed_int;
typedef int						el_int;
typedef signed long int			el_signed_long_int;
typedef signed long long int	el_signed_long_long_int;

// Unsigned integers
typedef unsigned short int		el_unsigned_short_int;
typedef unsigned int			el_unsigned_int;
typedef unsigned long int		el_unsigned_long_int;
typedef unsigned long long int	el_unsigned_long_long_int;

// Floating point
typedef float				el_float;
typedef double				el_double;
typedef long double			el_long_double;

// Specific
typedef bool				el_bool;
typedef void				el_void;

// Unusual
//typedef decltype(nullptr)	el_decltype(nullptr);

#if defined(WIN32) || defined(WINDOWS)
// Specific types
typedef clock_t				el_clock_t;
#endif

// Strings
typedef std::string		el_string;
typedef std::wstring	el_wstring;


#endif /* ELDEFINITIONS_H_ */
