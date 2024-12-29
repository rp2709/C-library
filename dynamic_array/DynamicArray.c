#include "DynamicArray.h"
#include <stdlib.h>

#include "../utils/generics_utils.h"

status DYNA_ALLOCATION_ERROR = {_ERROR,"Allocation error","Failed to allocate requested memory"};
status DYNA_ILLEGAL_OPERATION = {_WARNING,"Illegal operation","The operation cannot be performed but structure is intact and can be used again"};

status dyna_init(dynamic_array* dyna, sizetype object_size){
    dyna->object_size = object_size;
    dyna->data = nullptr;
    dyna->capacity = 0;
    dyna->length = 0;
    return dyna_reserve(dyna,1);
}

status dyna_reserve(dynamic_array* dyna, sizetype capacity){
    if(dyna->capacity >= capacity)
        return OK;

    arbitrary_pointer new_data = realloc(dyna->data,capacity * dyna->object_size);
    if (new_data == nullptr)
        return DYNA_ALLOCATION_ERROR;

    dyna->data = new_data;
    dyna->capacity = capacity;

    return OK;
}

status dyna_append(dynamic_array* dyna, arbitrary_pointer value){
    if(dyna->length >= dyna->capacity){
        const status rv = dyna_reserve(dyna,dyna->capacity * CAPACITY_FACTOR);
        if(!rv.success)
            return rv;
    }

    arbitrary_pointer next = dyna->data + dyna->length * dyna->object_size;
    memcopy(value,next,dyna->object_size);

    ++dyna->length;
    return OK;
}

status dyna_pop_back(dynamic_array* dyna){
    if(dyna->length == 0)
        return DYNA_ILLEGAL_OPERATION;

    --dyna->length;    

    return OK;
}

status dyna_at(dynamic_array* dyna, sizetype index, arbitrary_pointer result){
    if(index >= dyna->length)
        return ERROR;

    memcopy(dyna->data + index * dyna->object_size,result,dyna->object_size);

    return OK;
}

status dyna_free(dynamic_array* dyna) {
    if (dyna->data == nullptr)
        return DYNA_ILLEGAL_OPERATION;

    free(dyna->data);
    dyna->data = nullptr;

    return OK;
}