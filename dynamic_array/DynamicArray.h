#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define CAPACITY_FACTOR 2

#include "../utils/Types.h"
#include "../utils/Status.h"
#include "../allocator/Allocator.h"

extern status DYNA_ALLOCATION_ERROR;
extern status DYNA_ILLEGAL_OPERATION;

/**
 * Generic Dynamic Arrays
 * ALWAYS INITIALIZE THE ARRAY BEFORE USING IT
 * All methods are prefixed with dyna_
 */
typedef struct{
    arbitrary_pointer data;

    sizetype length;
    sizetype capacity;

    sizetype object_size;
    allocator_implementation* allocator;
}dynamic_array;

/**
 * Initialize a dynamic array of capacity 1
 * If allocator_implementation is nullptr, standard allocator will be used
 */
status dyna_init(dynamic_array* dyna, sizetype object_size, allocator_implementation* allocator);

/**
 * Allocates capacity for "size" elements
 */
status dyna_reserve(dynamic_array* dyna, sizetype size);

/**
 * Appends "value" at the back of the array
 */
status dyna_append(dynamic_array* dyna, arbitrary_pointer value);

/**
 * Removes the last element, but leaves capacity unchanged
 */
status dyna_pop_back(dynamic_array* dyna);


/**
 * Copies the object at "index" in result
 */
status dyna_get_at(dynamic_array* dyna, sizetype index, arbitrary_pointer result);

/**
 * Sets element at "index" to "value"
 */
status dyna_set_at(dynamic_array* dyna, sizetype index, arbitrary_pointer value);

/**
 * Destroys a dynamic array
 * does nothing if data is already nullptr
 */
status dyna_free(dynamic_array* dyna);

#endif