
#include "generics_utils.h"

void memcopy(arbitrary_pointer origin, arbitrary_pointer destination, sizetype size){
    for(sizetype i = 0; i < size; ++i)
        ((char*)destination)[i] = ((char*)origin)[i];
}

bool memequal(arbitrary_pointer a, arbitrary_pointer b, sizetype size) {
    for(sizetype i = 0; i < size; ++i)
        if (((char*)a)[i] != ((char*)b)[i])
            return false;
    return true;
}