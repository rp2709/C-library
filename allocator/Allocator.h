#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "../utils/Types.h"
#include "../utils/Status.h"
#include "../utils/generics_utils.h"

/**
 * An internal error occurred in the allocator, probably system not having enough memory
 */
extern const status ALLOCATION_ERROR;

/**
 * This is a basic allocator interface
 * All the library uses it, and therefor can easily use different allocator implementations
 * You get to tailor the data structures for space or time efficiency.
 */
struct allocator {
    arbitrary_pointer (*malloc)(sizetype size);
    void (*free)(arbitrary_pointer ptr);
    status (*realloc)(arbitrary_pointer* ptr, sizetype size);
};
typedef struct allocator allocator_implementation;

// ===== Implementations =====
/**
 * Fastest and simplest implementation, but will end up fragmenting memory
 * It performs even better than the standard, but if available, use standard for obvious safety reasons
 */
extern allocator_implementation FIRST_FIT;

/** Wrapper around C standard malloc library
 * Enables all project's data structures to use standard allocator as well
 * THIS IS THE ONE YOU WANT TO BE USING
 */
extern allocator_implementation STANDARD;

// - - - -  Future projects - - - -
//extern allocator_implementation BEST_FIT;
//extern allocator_implementation QUICK_FIT;

//#### DEBUG #####
void print_debug_info();

#endif //ALLOCATOR_H
