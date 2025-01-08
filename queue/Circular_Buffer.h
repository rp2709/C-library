#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "../utils/Status.h"
#include "../utils/Types.h"

#include "../allocator/Allocator.h"

typedef struct {
    arbitrary_pointer data;
    sizetype length;
    sizetype capacity;
    sizetype start_index;

    sizetype object_size;

    allocator_implementation* allocator;
}circular_buffer;

status cibu_init(circular_buffer *buffer, sizetype object_size, allocator_implementation* allocator);

status cibu_free(circular_buffer *buffer);

status cibu_reserve(circular_buffer *buffer, sizetype size);

status cibu_push_front(circular_buffer *buffer, arbitrary_pointer element);
status cibu_push_back(circular_buffer *buffer, arbitrary_pointer element);

status cibu_pop_front(circular_buffer *buffer);
status cibu_pop_back(circular_buffer *buffer);

status cibu_get_at(circular_buffer *buffer, sizetype index, arbitrary_pointer result);

#endif //CIRCULAR_BUFFER_H
