#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include "../utils/Types.h"
#include "../utils/Status.h"
#include "../utils/generics_utils.h"

struct allocator {
    arbitrary_pointer (*malloc)(sizetype size);
    status (*free)(arbitrary_pointer ptr);
    status (*realloc)(arbitrary_pointer* ptr, sizetype size);
};
typedef struct allocator allocator_implementation;

// ===== Implementations =====
// Fastest and simplest implementation, but will end up fragmenting memory
extern allocator_implementation FIRST_FIT;
extern allocator_implementation BEST_FIT;
extern allocator_implementation QUICK_FIT;
extern allocator_implementation STANDARD;

#endif //ALLOCATOR_H
