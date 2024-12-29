#ifndef TYPES_H
#define TYPES_H

// ===== INTEGERS =====

// ----- Sign & size -----

typedef signed char int8;
typedef unsigned char uint8;

typedef signed short int16;
typedef unsigned short uint16;

typedef signed int int32;
typedef unsigned int uint32;

typedef signed long long int64;
typedef unsigned long long uint64;

// ----- Special -----

typedef unsigned char byte;
typedef byte* byte_pointer;

typedef uint64 sizetype;

typedef void* arbitrary_pointer;

#define nullptr ((arbitrary_pointer)0)

typedef int8 bool;

#define true (bool)1
#define false (bool)0

// ===== REALS =====

typedef double real64;
typedef float real32;

typedef double real;

// ===== LIMITS =====

extern const sizetype NAN;

#endif //TYPES_H
