#ifndef STRING_H
#define STRING_H

#include "../dynamic_array/DynamicArray.h"

/**
 * ALWAYS USE ONE OF THE CONSTRUCTORS BEFORE ANYTHING ELSE
 *
 * Strings are just dynamic arrays of characters, you may therefore use any dyna method on a string.
 */
typedef dynamic_array string_t;

// ----- static method -----
void string_set_allocator(allocator_implementation* _allocator);

// ----- Constructors -----
status string_init(string_t * str, const char * basic_string);

status string_init_xchar(string_t* str, unsigned x, char c);

const char* string_get_c_string(const string_t * str);

status string_copy(string_t * dest, const string_t * origin);

status string_sub_from_to(string_t * dest, const string_t * origin, sizetype from, sizetype to);

status string_sub_from(string_t * dest, const string_t * origin, sizetype from);

status string_sub_to(string_t * dest, const string_t * origin, sizetype to);

// ----- destructor -----

void string_free(string_t * str);

// ----- modifying -----

status string_append(string_t * str, char c);

status string_concat(string_t * left, const string_t * right);

status string_set_at(string_t * str, sizetype pos, char c);

// ----- lookup -----

sizetype string_length(const string_t * str);

status string_get_at(const string_t * str, sizetype pos, char* c);

sizetype string_find_first_of(const string_t * str, char c, sizetype start_pos);

sizetype string_find_last_of(const string_t * str, char c, sizetype start_pos);

#endif //STRING_H
