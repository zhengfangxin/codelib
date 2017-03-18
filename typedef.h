#pragma once


// 常用类型
typedef signed long long		int64;		/* signed 64 bit value */
typedef unsigned long long		uint64;		/* signed 64 bit value */
typedef signed int				int32;		/* signed 32 bit value */
typedef unsigned int			uint32;		/* unsigned 32 bit value */
typedef signed short			int16;		/* signed 16 bit value */
typedef unsigned short			uint16;		/* unsigned 16 bit value */
typedef signed char				int8;		/* signed 8  bit value */
typedef unsigned char			uint8;		/* unsigned 8  bit value */
typedef unsigned short			word;		/* unsigned 16 bit value type. */
typedef unsigned int			dword;		/* unsigned 32 bit value type. */

typedef unsigned int			uint;
typedef unsigned short			ushort;
typedef unsigned char			uchar;


#define ARSIZE(AR) (sizeof(AR)/sizeof(AR[0]))

#ifdef _WINDOWS

#else

#ifndef NULL
#define NULL 0
#endif

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

#endif