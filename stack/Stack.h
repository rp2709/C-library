#ifndef STACK_H
#define STACK_H

#include "../dynamic_array/DynamicArray.h"

typedef dynamic_array stack;

status stack_init(stack *s, sizetype object_size);

status stack_free(stack *s);

status stack_push(stack *s, arbitrary_pointer value);
status stack_pop(stack *s, arbitrary_pointer value);
status stack_peek(stack *s, arbitrary_pointer value);

#endif //STACK_H
