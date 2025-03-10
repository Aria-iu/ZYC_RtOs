//
// Created by zyc on 25-3-10.
//

#ifndef ZYC_TYPES_H
#define ZYC_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

    // typedef unsigned long uintptr_t;
    typedef unsigned char U8;
    typedef unsigned short U16;
    typedef unsigned int U32;
    typedef unsigned long long U64;
    typedef signed char S8;
    typedef signed short S16;
    typedef signed int S32;
    typedef signed long long S64;

    typedef void *VirtAddr;
    typedef void *PhyAddr;

#ifndef OS_SEC_ALW_INLINE
#define OS_SEC_ALW_INLINE
#endif

#ifndef INLINE
#define INLINE static __inline __attribute__((always_inline))
#endif

#ifndef OS_EMBED_ASM
#define OS_EMBED_ASM __asm__ __volatile__
#endif

    /* 参数不加void表示可以传任意个参数 */
    typedef void (*OsVoidFunc)(void);

#define ALIGN(addr, boundary) (((uintptr_t)(addr) + (boundary) - 1) & ~((uintptr_t)(boundary) - 1))
#define TRUNCATE(addr, size)  ((addr) & ~((uintptr_t)(size) - 1))

#ifdef YES
#undef YES
#endif
#define YES 1

#ifdef NO
#undef NO
#endif
#define NO 0

#ifndef FALSE
#define FALSE ((bool)0)
#endif

#ifndef TRUE
#define TRUE ((bool)1)
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define OS_ERROR   (U32)(-1)
#define OS_INVALID (-1)

#ifndef OS_OK
#define OS_OK 0
#endif

#ifndef OS_FAIL
#define OS_FAIL 1
#endif

#ifndef U8_INVALID
#define U8_INVALID 0xffU
#endif

#ifndef U12_INVALID
#define U12_INVALID 0xfffU
#endif

#ifndef U16_INVALID
#define U16_INVALID 0xffffU
#endif

#ifndef U32_INVALID
#define U32_INVALID 0xffffffffU
#endif

#ifndef U64_INVALID
#define U64_INVALID 0xffffffffffffffffUL
#endif

#ifndef U32_MAX
#define U32_MAX 0xFFFFFFFFU
#endif

#ifndef S32_MAX
#define S32_MAX 0x7FFFFFFF
#endif

#ifndef S32_MIN
#define S32_MIN (-S32_MAX-1)
#endif

#ifndef LIKELY
#define LIKELY(x) __builtin_expect(!!(x), 1)
#endif

#ifndef UNLIKELY
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

#endif //ZYC_TYPES_H
