#include "LinkedList.h"

#include <stdlib.h>

void node_free(_node* node) {
    if (node == nullptr)
        return;
    if (node->data != nullptr)
        free(node->data);
    free(node);
}

// ===== List manipulation with iterators =====

list_iterator list_begin(list* l) {
    const list_iterator b = {(_node*)l,l};
    return b;
}

bool list_has_next(const list_iterator iterator) {
    if (iterator.current == nullptr)
        return false;
    return (bool)(iterator.current->next != nullptr);
}

status list_next(list_iterator* iterator) {
    if (iterator->current == nullptr) {
        return ERROR;
    }
    iterator->current = (_node*)iterator->current->next;
    return OK;
}

status list_at(const list_iterator iterator, arbitrary_pointer value) {
    if (iterator.current == nullptr)
        return ERROR;
    if (iterator.current->next == nullptr)
        return ERROR;

    memcopy(((_node*)(iterator.current->next))->data, value, iterator.list->object_size);

    return OK;
}

status list_insert(const list_iterator iterator, arbitrary_pointer value) {
    _node* new_node = malloc(sizeof(_node));
    if (new_node == nullptr)
        return ERROR;
    new_node->data = malloc(iterator.list->object_size);
    if (new_node->data == nullptr) {
        node_free(new_node);
        return ERROR;
    }

    memcopy(value, new_node->data, iterator.list->object_size);

    _node* next = (_node*)iterator.current->next;
    new_node->next = (struct _node*)next;
    iterator.current->next = (struct _node*)new_node;

    return OK;
}

status list_remove(const list_iterator iterator) {
    if (iterator.current->next == nullptr)
        return ERROR;

    _node* removed_node = (_node*)iterator.current->next;
    iterator.current->next = removed_node->next;
    node_free(removed_node);
    return OK;
}

// ===== Basic list operations =====

status list_init(list* l, sizetype object_size) {
    l->head = nullptr;
    l->object_size = object_size;
    return OK;
}

void node_recursive_free(_node* node) {
    if (node == nullptr)
        return;
    node_recursive_free((_node*)node->next);
    node_free(node);
}

status list_free(list* l) {
    node_recursive_free((_node*)l->head);
    return OK;
}

status list_add_front(list* l, arbitrary_pointer value) {
    return list_insert(list_begin(l), value);
}