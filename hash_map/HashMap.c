#include "HashMap.h"

#include <stdlib.h>

void hm_pair_free(_hmap_pair* pair) {
    if (pair == nullptr) return;
    if (pair->key != nullptr) {
        free(pair->key);
        pair->key = nullptr;
    }
    if (pair->value != nullptr) {
        free(pair->value);
        pair->value = nullptr;
    }
}

sizetype bucket_index(const hash_map* hm, arbitrary_pointer key) {
    return hm->hash(key) % hm->capacity;
}

status hmap_init(hash_map *map, sizetype key_size, sizetype value_size, sizetype initial_capacity, hash_function hash, equal_function is_equal) {
    map->key_size = key_size;
    map->value_size = value_size;

    map->is_equal = is_equal;
    map->hash = hash;

    map->buckets = malloc(initial_capacity * sizeof(list));
    if (map->buckets == nullptr)
        return ERROR;

    for (sizetype i = 0; i < initial_capacity; ++i) {
        status rv = list_init(&(map->buckets[i]),sizeof(_hmap_pair));
        if (!rv.success)
            return rv;
    }
    map->capacity = initial_capacity;

    return OK;
}

status hmap_free(hash_map *map) {
    for (sizetype i = 0; i < map->capacity; ++i) {
        list* bucket = &(map->buckets[i]);

        _hmap_pair pair;
        for (list_iterator it = list_begin(bucket); list_has_next(it); list_next(&it)) {
            list_at(it, &pair);
            hm_pair_free(&pair);
        }

        list_free(bucket);
    }
}

status hmap_insert(hash_map *map, arbitrary_pointer key, arbitrary_pointer value) {
    list* bucket = &(map->buckets[bucket_index(map,key)]);

    arbitrary_pointer value_storage = malloc(map->value_size);
    if (value_storage == nullptr)
        return ERROR;
    arbitrary_pointer key_storage = malloc(map->key_size);
    if (key_storage == nullptr) {
        free(value_storage);
        return ERROR;
    }

    memcopy(key,key_storage,map->key_size);
    memcopy(value,value_storage,map->value_size);

    _hmap_pair pair = {key_storage,value_storage};

    list_add_front(bucket,&pair);
    return OK;
}

status hmap_set(hash_map *map, arbitrary_pointer key, arbitrary_pointer value);

status hmap_remove(hash_map *map, arbitrary_pointer key);

status hmap_get(const hash_map *map, arbitrary_pointer key, arbitrary_pointer value) {
    list* bucket = &(map->buckets[bucket_index(map,key)]);
    _hmap_pair pair;
    for (list_iterator it = list_begin(bucket); list_has_next(it); list_next(&it)) {
        list_at(it,&pair);
        if (memequal(key,pair.key,map->key_size)) {
            memcopy(pair.value,value,map->value_size);
            return OK;
        }
    }
    return ERROR;
}