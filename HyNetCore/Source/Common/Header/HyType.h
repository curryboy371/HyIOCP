#pragma once
/* Type define list */


/* 기본 자료형 재정의 */
#pragma region Types
//~ Unsigned base types from Unreal...

// 8-bit unsigned integer
typedef unsigned char 		uint8;

// 16-bit unsigned integer
typedef unsigned short int	uint16;

// 32-bit unsigned integer
typedef unsigned int		uint32;

// 64-bit unsigned integer
typedef unsigned long long	uint64;

//~ Signed base types.

// 8-bit signed integer
typedef	signed char			int8;

// 16-bit signed integer
typedef signed short int	int16;

// 32-bit signed integer
typedef signed int	 		int32;

// 64-bit signed integer
typedef signed long long	int64;

//~ Character types

// An ANSI character.
typedef char				ANSICHAR;

// A wide character.
typedef wchar_t				WIDECHAR;

// An 8-bit character type.
typedef uint8				CHAR8;

// A 16-bit character type.
typedef uint16				CHAR16;

// A 32-bit character type. 
typedef uint32				CHAR32;

// A switchable character.
typedef WIDECHAR			TCHAR;
#pragma endregion

/* shared_ptr 재정의 */
#pragma region UsingMacro
#define USING_SHARED_PTR(Cname)		using Cname##Ref = std::shared_ptr<class Cname>;







#pragma endregion


