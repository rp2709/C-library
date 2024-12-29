
#include "generics_utils.h"

void memcopy(arbitrary_pointer origin, arbitrary_pointer destination, sizetype size){
    for(sizetype i = 0; i < size; ++i)
        ((char*)destination)[i] = ((char*)origin)[i];
}