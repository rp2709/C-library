#include "Allocator.h"

// Standard implementation wrapper
#include <stdlib.h>
arbitrary_pointer stdmalloc(sizetype size) {
    return malloc(size);
}

status stdfree(arbitrary_pointer ptr) {
    free(ptr);
    return OK;
}

status stdrealloc(arbitrary_pointer* ptr, sizetype size) {
    arbitrary_pointer old = *ptr;
    *ptr = realloc(*ptr, size);
    if (*ptr == nullptr) {
        *ptr = old;
        return ERROR;
    }
    return OK;
}

allocator_implementation STANDARD = {
    stdmalloc,
    stdfree,
    stdrealloc
};