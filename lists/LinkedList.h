#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "../utils/generics_utils.h"
#include "../utils/Status.h"
#include "../utils/Types.h"

typedef struct {
    struct _node* next;
    arbitrary_pointer data;
}_node;

typedef struct {
    _node* head;
    sizetype object_size;
}list;

typedef struct {
    _node* current;
    list* list;
} list_iterator;

// ===== List manipulation with iterators =====

bool list_has_next(const list_iterator iterator);

list_iterator list_begin(list* l);

status list_next(list_iterator* iterator);

status list_at(list_iterator iterator, arbitrary_pointer value);

status list_insert(list_iterator iterator, arbitrary_pointer value);

status list_remove(list_iterator iterator);

// ===== Basic list operations =====

status list_init(list* l, sizetype object_size);

status list_free(list* l);

status list_add_front(list* l, arbitrary_pointer value);

#endif //LINKEDLIST_H
