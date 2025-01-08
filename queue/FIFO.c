#include "FIFO.h"

status fifo_init(fifo *f, sizetype object_size, allocator_implementation *allocator) {
    return cibu_init(f,object_size,allocator);
}

status fifo_reserve(fifo *f, sizetype size) {
    return cibu_reserve(f,size);
}

status fifo_push(fifo *f, arbitrary_pointer value) {
    return cibu_push_front(f,value);
}

status fifo_pop(fifo *f, arbitrary_pointer value) {
    status s = fifo_peek(f,value);
    if (!s.success)
        return s;
    return cibu_pop_back(f);
}

status fifo_peek(fifo *f, arbitrary_pointer value) {
    return cibu_get_at(f,f->length - 1,value);
}

status fifo_put_back(fifo *f, arbitrary_pointer value) {
    return cibu_push_back(f,value);
}

status fifo_free(fifo *f) {
    return cibu_free(f);
}