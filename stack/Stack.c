#include "Stack.h"

status stack_init(stack *s, sizetype object_size) {
    return dyna_init(s,object_size);
}

status stack_free(stack *s) {
    return dyna_free(s);
}

status stack_push(stack *s, arbitrary_pointer value) {
    return dyna_append(s,value);
}
status stack_pop(stack *s, arbitrary_pointer value) {
    dyna_at(s,s->length - 1,value);
    return dyna_pop_back(s);
}
status stack_peek(stack *s, arbitrary_pointer value) {
    return dyna_at(s,s->length - 1,value);
}