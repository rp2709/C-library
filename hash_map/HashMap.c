#include "HashMap.h"

void hm_pair_free(_hmap_pair* pair, allocator_implementation* allocator) {
    if (pair == nullptr) return;
    if (pair->key != nullptr) {
        allocator->free(pair->key);
        pair->key = nullptr;
    }
    if (pair->value != nullptr) {
        allocator->free(pair->value);
        pair->value = nullptr;
    }
}

sizetype bucket_index(const hash_map* hm, arbitrary_pointer key) {
    return hm->hash(key) % hm->capacity;
}

status hmap_init(hash_map *map, sizetype key_size, sizetype value_size, sizetype initial_capacity, hash_function hash, equal_function is_equal, allocator_implementation* allocator) {
    map->allocator = allocator;

    map->key_size = key_size;
    map->value_size = value_size;

    map->is_equal = is_equal;
    map->hash = hash;

    map->buckets = map->allocator->malloc(initial_capacity * sizeof(list));
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
            hm_pair_free(&pair,map->allocator);
        }
        list_free(bucket);
    }
    map->capacity = 0;
    return OK;
}

status hmap_insert(hash_map *map, arbitrary_pointer key, arbitrary_pointer value) {
    list* bucket = &(map->buckets[bucket_index(map,key)]);

    arbitrary_pointer value_storage = map->allocator->malloc(map->value_size);
    if (value_storage == nullptr)
        return ERROR;
    arbitrary_pointer key_storage = map->allocator->malloc(map->key_size);
    if (key_storage == nullptr) {
        map->allocator->free(value_storage);
        return ERROR;
    }

    memcopy(key,key_storage,map->key_size);
    memcopy(value,value_storage,map->value_size);

    _hmap_pair pair = {key_storage,value_storage};

    list_add_front(bucket,&pair);
    return OK;
}

status find_and_apply(hash_map *map, arbitrary_pointer key, arbitrary_pointer value,
                      void(*function)(arbitrary_pointer, arbitrary_pointer, sizetype))
{
    list* bucket = &(map->buckets[bucket_index(map,key)]);
    _hmap_pair pair;
    for (list_iterator it = list_begin(bucket); list_has_next(it); list_next(&it)) {
        list_at(it,&pair);
        if (memequal(key,pair.key,map->key_size)) {
            function(value,pair.value,map->value_size);
            return OK;
        }
    }
    return ERROR;
}

void set_apply(arbitrary_pointer value, arbitrary_pointer destination, sizetype value_size) {
    memcopy(value,destination,value_size);
}

status hmap_set(hash_map *map, arbitrary_pointer key, arbitrary_pointer value) {
    return find_and_apply(map, key, value, set_apply);
}

void get_apply(arbitrary_pointer destination, arbitrary_pointer value, sizetype value_size) {
    memcopy(value,destination,value_size);
}

status hmap_get(const hash_map *map, arbitrary_pointer key, arbitrary_pointer value) {
    return find_and_apply((hash_map*)map, key, value, get_apply);
}

status hmap_remove(hash_map *map, arbitrary_pointer key) {
    list* bucket = &(map->buckets[bucket_index(map,key)]);
    _hmap_pair pair;
    for (list_iterator it = list_begin(bucket); list_has_next(it); list_next(&it)) {
        list_at(it,&pair);
        if (memequal(key,pair.key,map->key_size)) {
            list_remove(it);
            hm_pair_free(&pair,map->allocator);
            return OK;
        }
    }
    return ERROR;
}