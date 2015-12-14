#pragma once

#include <DirectXMath.h>

#define USE_SIMD

#ifdef USE_SIMD
    #ifdef _WIN32

        // definitions for defining alignment for our classes
        #define ALIGNED16(type)  __declspec(align(16))  type
        #define ALIGNED64(type)  __declspec(align(64))  type
        #define ALIGNED128(type) __declspec(align(128)) type
    
        // needed to use intrinsic functions
        #include <intrin.h>
    
        // typedef the SIMD structure
        typedef __m128 SIMD128;

    #endif // _WIN32
#endif // USE_SIMD
