#include "HashMap.h"

#include <stdio.h>
#include <stdlib.h>

int main() {

    hash_map map;
    hmap_init(&map,sizeof(int),sizeof(real),10,nullptr);

    real val;

    for (int i = 0; i < 10; i++) {
        val = rand() / 6500000.4;
        hmap_insert(&map,&i,&val);
    }

    for (int i = 0; i < 10; i++) {
        hmap_get(&map,&i,&val);
        printf("Key : %d, Value %f\n",i,val);
    }

    return 0;
}
