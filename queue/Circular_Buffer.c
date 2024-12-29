//
// Created by raphael on 12/28/24.
//

#include "Circular_Buffer.h"

#include <stdlib.h>

#include "../utils/generics_utils.h"

sizetype physical_index(circular_buffer *cb, sizetype logical_index) {
    return (cb->start_index + logical_index) % cb->capacity;
}

status cibu_init(circular_buffer *buffer, sizetype object_size) {
    buffer->start_index = 0;
    buffer->capacity = 0;
    buffer->object_size = object_size;
    buffer->length = 0;
    buffer->data = nullptr;
    return cibu_reserve(buffer,1);
}

status cibu_free(circular_buffer *buffer) {
    if (buffer->data == nullptr) {
        return WARNING;
    }
    free(buffer->data);
    buffer->data = nullptr;
}

status cibu_reserve(circular_buffer *buffer, sizetype size) {
    if (buffer->capacity >= size)
        return WARNING;

    arbitrary_pointer new_data = malloc(size * buffer->object_size);

    if (new_data == nullptr)
        return ERROR;

    for (sizetype i = 0; i < buffer->length; ++i) {
        memcopy(buffer->data + physical_index(buffer, i) * buffer->object_size,
                new_data + i * buffer->object_size,
                buffer->object_size);
    }
    if (buffer->data != nullptr)
        free(buffer->data);

    buffer->data = new_data;
    buffer->capacity = size;
    buffer->start_index = 0;
    return OK;
}

status cibu_push_front(circular_buffer *buffer, arbitrary_pointer element) {
    if (buffer->length >= buffer->capacity) {
        status s = cibu_reserve(buffer, buffer->capacity * 2);
        if (!s.success) {
            return s;
        }
    }

    buffer->start_index = (buffer->start_index + buffer->capacity - 1) % buffer->capacity;

    memcopy(element,
            buffer->data + physical_index(buffer, 0) * buffer->object_size,
            buffer->object_size);

    ++buffer->length;

    return OK;
}

status cibu_push_back(circular_buffer *buffer, arbitrary_pointer element) {
    if (buffer->length >= buffer->capacity) {
        status s = cibu_reserve(buffer, buffer->capacity * 2);
        if (!s.success) {
            return s;
        }
    }

    memcopy(element,buffer->data + physical_index(buffer, buffer->length) * buffer->object_size,buffer->object_size);
    ++buffer->length;

    return OK;
}

status cibu_pop_front(circular_buffer *buffer) {
    if (buffer->length == 0)
        return WARNING;
    buffer->start_index = (buffer->start_index + 1) % buffer->capacity;
    --buffer->length;
    return OK;
}

status cibu_pop_back(circular_buffer *buffer) {
    if (buffer->length == 0)
        return WARNING;
    --buffer->length;
    return OK;
}

status cibu_get_at(circular_buffer *buffer, sizetype index, arbitrary_pointer result) {
    if (index >= buffer->length)
        return ERROR;
    memcopy(buffer->data + physical_index(buffer, index) * buffer->object_size,result,buffer->object_size);
    return OK;
}
