#ifndef GENERICS_UTILS_H
#define GENERICS_UTILS_H

#include "Types.h"

void memcopy(arbitrary_pointer origin, arbitrary_pointer destination, sizetype size);

bool memequal(arbitrary_pointer a, arbitrary_pointer b, sizetype size);

#endif //GENERICS_UTILS_H
