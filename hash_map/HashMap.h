#ifndef HASHMAP_H
#define HASHMAP_H

#include "../lists/LinkedList.h"

typedef sizetype (*universal_hash_function)(arbitrary_pointer key,sizetype key_size);

sizetype basic_universal_hash(arbitrary_pointer key, sizetype key_size);

typedef struct {
    arbitrary_pointer key;
    arbitrary_pointer value;
}_hmap_pair;

typedef struct{
    sizetype key_size, value_size;
    universal_hash_function hash_function;
    list* buckets;
    sizetype capacity;
}hash_map;

// leave hash_function as nullptr to use default one
status hmap_init(hash_map *map, sizetype key_size, sizetype value_size, sizetype initial_capacity, universal_hash_function hash_function);

status hmap_free(hash_map *map);

status hmap_insert(hash_map *map, arbitrary_pointer key, arbitrary_pointer value);

status hmap_set(hash_map *map, arbitrary_pointer key, arbitrary_pointer value);

status hmap_remove(hash_map *map, arbitrary_pointer key);

status hmap_get(const hash_map *map, arbitrary_pointer key, arbitrary_pointer value);



#endif //HASHMAP_H
