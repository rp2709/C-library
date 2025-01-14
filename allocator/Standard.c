#include "Allocator.h"

// Standard implementation wrapper
#include <stdlib.h>
arbitrary_pointer stdmalloc(sizetype size) {
    return malloc(size);
}

void stdfree(arbitrary_pointer ptr) {
    free(ptr);
}

status stdrealloc(arbitrary_pointer* ptr, sizetype size) {
    arbitrary_pointer old = *ptr;
    *ptr = realloc(*ptr, size);
    if (*ptr == nullptr) {
        *ptr = old;
        return ALLOCATION_ERROR;
    }
    return OK;
}

allocator_implementation STANDARD = {
    stdmalloc,
    stdfree,
    stdrealloc
};