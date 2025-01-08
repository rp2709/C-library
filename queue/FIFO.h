#ifndef FIFO_H
#define FIFO_H

#include "../utils/Types.h"
#include "../allocator/Allocator.h"
#include "Circular_Buffer.h"

typedef circular_buffer fifo;

status fifo_init(fifo *f, sizetype object_size, allocator_implementation* allocator);

status fifo_free(fifo *f);

status fifo_reserve(fifo *f, sizetype size);

status fifo_push(fifo *f, arbitrary_pointer value);

status fifo_pop(fifo *f, arbitrary_pointer value);

status fifo_peek(fifo *f, arbitrary_pointer value);

status fifo_put_back(fifo *f, arbitrary_pointer value);

#endif //FIFO_H
