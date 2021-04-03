#ifndef CTL_PLATFORM_H
#define CTL_PLATFORM_H

// If the build system not defined macros
// we try to get them using pre-processor methods
#if !defined(ARCH_64BITS) && !defined(ARCH_32BITS)
#   if defined(__amd64__) || defined(_WIN64) || __SIZEOF_POINTER__ == 8    // 64 bits
#       define ARCH_64BITS
#   elif defined(__x86_64__) || defined(_WIN32) || __SIZEOF_POINTER__ == 4 // 32 bits
#       define ARCH_32BITS
#   else
#       error Unsupported architecture
#   endif
#endif

#if !defined(CYBEGON_COMPILER_GCC) && !defined(CYBEGON_COMPILER_MSVC)
#   if defined(__clang__)
#       define CYBEGON_COMPILER_CLANG
#   elif defined(__MINGW32__) || defined(__MINGW64__)
#       define CYBEGON_COMPILER_MINGW
#       define CYBEGON_COMPILER_GCC
#   elif defined(__GNUC__) || defined(__GNUG__)
#       define CYBEGON_COMPILER_GCC
#   elif defined(_MSC_VER)
#       define CYBEGON_COMPILER_MSVC
#   else
#       error Unsupported compiler
#   endif
#endif

#if !defined(CYBEGON_PLATFORM_WINDOWS) || !defined(CYBEGON_PLATFORM_UNIX)
#   if defined(_WIN32) || defined(_WIN64)
#       define CYBEGON_PLATFORM_WINDOWS
#   elif defined(unix) || defined(__unix__) || defined(__unix)
#       define CYBEGON_PLATFORM_UNIX
#       if defined(__linux__)
#           define CYBEGON_PLATFORM_LINUX
#       elif defined(__APPLE__)
#           define CYBEGON_PLATFORM_APPLE
#       elif defined(__ANDROID__)
#           define CYBEGON_PLATFORM_ANDROID
#       elif defined(__FreeBSD__)
#           define CYBEGON_PLATFORM_FREEBSD
#       elif defined(__OpenBSD__)
#           define CYBEGON_PLATFORM_OPENBSD
#       endif
#   else
#       error Unsupported platform
#   endif
#endif

#endif //CTL_PLATFORM_H
