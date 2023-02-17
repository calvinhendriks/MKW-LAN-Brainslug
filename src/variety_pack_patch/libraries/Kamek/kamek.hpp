/*
 * Kamek Standard Library
 * Wii game patching engine
 * (c) Treeki 2010-2018
 */

#define abs(n) __abs(n)


#ifndef __KAMEK_H
#define __KAMEK_H

/*#ifndef __MWERKS__
#error "Kamek requires the CodeWarrior compiler!"
#endif*/

#define NULL 0

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef signed long long s64;
typedef float f32;
typedef double f64;
typedef volatile s64 vs64;
typedef volatile s32 vs32;
typedef volatile s16 vs16;
typedef volatile s8 vs8;
typedef volatile u64 vu64;
typedef volatile u32 vu32;
typedef volatile u16 vu16;
typedef volatile u8 vu8;
typedef volatile f64 vf64;
typedef volatile f32 vf32;
typedef int UnkType;

typedef unsigned long size_t;

#define NODE_TO_ITEM(node, type, field) \
    ((type *)((char *)node - offsetof(type, field)))
    
#define offsetof(st, m) \
    ((u32)&(((st *)0)->m))

#ifdef __INTELLISENSE__
inline void * operator new(unsigned long long,  void * ptr) { return ptr; }
#define ASM(...)
#define asm
#define __attribute(...)
#define __sync(...)
#define __isync(...)
#else
inline void * operator new(size_t size,  void * ptr) { return ptr; }
#define ASM(...) __VA_ARGS__
#endif

#include "base/hooks.hpp"
#include "base/c_stdlib.hpp"
#include "base/rvl_sdk.h"
#include "base/math.hpp"

#endif

