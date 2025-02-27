#include "HashMap.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This exemple is going to use simple c strings

bool str_equal(arbitrary_pointer str1, arbitrary_pointer str2) {
    return (bool)(strcmp(str1,str2) == 0);
}

sizetype str_hash(arbitrary_pointer str) {
    sizetype hash = 0;
    for (int i = 0; i < strlen(str); i++) {
        hash += ((const char*)str)[i];
    }
    return hash;
}

enum transport {SHIP,PLANE,CAR,BIKE,BOAT};

int main() {

    hash_map map;
    hmap_init(&map,sizeof(const char*),sizeof(enum transport),10,str_hash,str_equal,&FIRST_FIT);

    enum transport value;
    value = SHIP;
    hmap_insert(&map,"SHIP",&value);
    value = PLANE;
    hmap_insert(&map,"PLANE",&value);
    value = CAR;
    hmap_insert(&map,"CAR",&value);
    value = BIKE;
    hmap_insert(&map,"BIKE",&value);
    value = BOAT;
    hmap_insert(&map,"BOAT",&value);

    pedantic_assert(hmap_get(&map,"SHIP",&value));
    pedantic_assert(hmap_get(&map,"PLANE",&value));
    pedantic_assert(hmap_get(&map,"CAR",&value));
    pedantic_assert(hmap_get(&map,"BIKE",&value));
    pedantic_assert(hmap_get(&map,"BOAT",&value));

    pedantic_assert(hmap_remove(&map,"BOAT"));

    pedantic_assert(hmap_get(&map,"SHIP",&value));
    pedantic_assert(hmap_get(&map,"PLANE",&value));
    pedantic_assert(hmap_get(&map,"CAR",&value));
    pedantic_assert(hmap_get(&map,"BIKE",&value));
    //this next line causes an expected crash
    pedantic_assert(hmap_get(&map,"BOAT",&value));

    hmap_free(&map);

    return 0;
}
