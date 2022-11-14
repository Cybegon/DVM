#ifndef DATATYPE_GLOBAL_H
#define DATATYPE_GLOBAL_H

#include "platform.h"

#define KB(VALUE) ( VALUE * 1024 )
#define MB(VALUE) ( VALUE * 1024 * 1024 )
#define GB(VALUE) ( VALUE * 1024 * 1024 * 1024 )

#define ALIGN_SIZE(s, a) (s / a + 1) * a
#define ALIGN_ADDRESS(s, a) ALIGN_SIZE(s, a)

//#ifdef defined(CYBEGON_COMPILER_GCC)
//#   define DVM_CALLBACK __cdecl
//#   define DVM_FASTCALL __fastcall
//#elif defined(CYBEGON_COMPILER_MSVC)
//#   define DVM_CALLBACK __cdecl
//#   define DVM_FASTCALL __fastcall
//#endif // CYBEGON_COMPILER_MSVC


#if defined(CYBEGON_COMPILER_GCC) || defined(CYBEGON_COMPILER_CLANG)
#   define PACKED_BEGIN
#   define PACKED  __attribute__((__packed__))
#   define PACKED_END
#elif defined(CYBEGON_COMPILER_MSVC)
#   define PACKED_BEGIN __pragma(pack(push, 1))
#   define PACKED
#   define PACKED_END __pragma(pack(pop))
#else
#   warning PACKED macros are not defined for this compiler
#endif

#if defined(CYBEGON_PLATFORM_WINDOWS)
#   define CYBEGON_EXPORT    __declspec(dllexport)
#   define CYBEGON_IMPORT    __declspec(dllimport)
#elif defined(CYBEGON_PLATFORM_UNIX)
#   define CYBEGON_EXPORT    __attribute__((visibility("default")))
#   define CYBEGON_IMPORT    __attribute__((visibility("default")))
#else
#   define CYBEGON_EXPORT
#   define CYBEGON_IMPORT
#endif

#if !defined(M_PI)
#   define M_PI			3.14159265358979323846
#endif

#if !defined(MIN)
#   define MIN(a,b) ( ((a) < (b)) ? (a) : (b) )
#endif

#if !defined(MAX)
#   define MAX(a,b) ( ((a) > (b)) ? (a) : (b) )
#endif

#if defined(__cplusplus)
#   define BEGIN_EXTERN_C extern "C" {
#   define END_EXTERN_C }
#   define POINTER_CAST(TYPE, POINTER) ( reinterpret_cast<TYPE>(POINTER) )
#else
#   define BEGIN_EXTERN_C
#   define END_EXTERN_C
#   define POINTER_CAST(TYPE, POINTER) ( (TYPE) POINTER )
#endif

#if !defined(NULL)
#   if defined(__cplusplus)
#       if defined(ARCH_64BITS)
#           define NULL 0LL
#       else
#           define NULL 0
#       endif
#   else
#       define NULL ((void*)0)
#   endif
#endif

#if !defined(TRUE)
#   define TRUE 1
#endif

#if !defined(FALSE)
#   define FALSE 0
#endif

#if defined(__cplusplus)
#   define abstract
#   define interface    class
#endif

typedef unsigned char   duchar;
typedef unsigned short  dushort;
typedef int             dint;      // 32 bit signed
typedef unsigned int   	duint;     // 32 bit unsigned
typedef unsigned long   dulong;
typedef char           *dpchar;
typedef duchar         *dpuchar;

typedef unsigned char   		duint8;    // 8 bit unsigned
typedef short           		dint16;    // 16 bit signed
typedef unsigned short  		duint16;   // 16 bit unsigned
typedef int             		dint32;    // 32 bit signed
typedef signed char     		dint8;     // 8 bit signed
typedef unsigned int   			duint32;   // 32 bit unsigned
#if defined(ARCH_64BITS) && defined(CYBEGON_PLATFORM_APPLE)
typedef long       		        dint64;    // 64 bit signed
typedef unsigned long   	    duint64;   // 64 bit unsigned
#else
typedef long long       		dint64;    // 64 bit signed
typedef unsigned long long   	duint64;   // 64 bit unsigned
#endif
typedef unsigned char           dbyte;

#if defined(ARCH_64BITS)
typedef duint64          		dsize;
#elif defined(ARCH_64BITS) && defined(CYBEGON_PLATFORM_APPLE)
typedef dulong          		dsize;
#elif defined(ARCH_32BITS)
typedef duint32          		dsize;
#else
#   error Unsupported architecture
#endif

#if !defined(DT_DISABLE_VOID) || !defined(VOID)
typedef void                    VOID;
#endif
typedef void*           	    DESCRIPTOR;
typedef void*           	    POINTER;
typedef POINTER                 MEMORY;
typedef POINTER                 ADDRESS;

#endif //DATATYPE_GLOBAL_H
