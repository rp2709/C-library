#ifndef FIFO_H
#define FIFO_H
#include <stddef.h>

#include "Circular_Buffer.h"

typedef circular_buffer fifo;

status fifo_init(fifo *f, sizetype object_size);

status fifo_free(fifo *f);

status fifo_reserve(fifo *f, size_t size);

status fifo_push(fifo *f, arbitrary_pointer value);

status fifo_pop(fifo *f, arbitrary_pointer value);

status fifo_peek(fifo *f, arbitrary_pointer value);

status fifo_put_back(fifo *f, arbitrary_pointer value);

#endif //FIFO_H
