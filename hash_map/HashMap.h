#ifndef HASHMAP_H
#define HASHMAP_H

#include "../lists/LinkedList.h"
#include "../allocator/Allocator.h"

typedef sizetype (*hash_function)(arbitrary_pointer key);
typedef bool (*equal_function)(arbitrary_pointer a, arbitrary_pointer b);

typedef struct {
    arbitrary_pointer key;
    arbitrary_pointer value;
}_hmap_pair;

typedef struct{
    sizetype key_size, value_size;

    hash_function hash;
    equal_function is_equal;

    list* buckets;
    sizetype capacity;

    allocator_implementation* allocator;
}hash_map;

// leave hash_function as nullptr to use default one
status hmap_init(hash_map *map, sizetype key_size, sizetype value_size, sizetype initial_capacity, hash_function hash, equal_function is_equal, allocator_implementation* allocator);

status hmap_free(hash_map *map);

status hmap_insert(hash_map *map, arbitrary_pointer key, arbitrary_pointer value);

status hmap_set(hash_map *map, arbitrary_pointer key, arbitrary_pointer value);

status hmap_remove(hash_map *map, arbitrary_pointer key);

status hmap_get(const hash_map *map, arbitrary_pointer key, arbitrary_pointer value);



#endif //HASHMAP_H
