#include "String.h"

#include "../utils/generics_utils.h"

const char null_char = '\0';

allocator_implementation * allocator;

void string_set_allocator(allocator_implementation* _allocator) {
    allocator = _allocator;
}

sizetype c_string_length(const char* s) {
    sizetype length = 0;
    while (s[length])
        ++length;
    return length;
}

// ----- Constructors -----
status string_init(string_t * str, const char * basic_string){
    status rv = dyna_init(str,sizeof(char),allocator);
    if (!rv.success)
        return rv;

    sizetype len = c_string_length(basic_string) + 1; // + 1 because we want to keep null termination
    rv = dyna_reserve(str,len);
    if (!rv.success)
        return rv;

    memcopy((arbitrary_pointer)basic_string,str->data,len * sizeof(char));
    str->length = len;
    return OK;
}

status string_init_xchar(string_t* str, unsigned x, char c) {
    status rv = dyna_init(str,sizeof(char),allocator);
    if (!rv.success)return rv;

    rv = dyna_reserve(str,x+1);
    if (!rv.success)return rv;

    for (unsigned i = 0; i < x; i++) {
        rv = dyna_append(str,&c);
        if (!rv.success)return rv;
    }
    rv = dyna_append(str,&null_char);
    if (!rv.success)return rv;

    return OK;
}

const char* string_get_c_string(const string_t * str) {
    return str->data;
}

status string_copy(string_t * dest, const string_t * origin) {
    dyna_reserve(dest,origin->length + 1);
    memcopy(origin->data,dest->data,(origin->length + 1) * sizeof(char));
    dest->length = origin->length;
    return OK;
}

status string_sub_from_to(string_t * dest, const string_t * origin, sizetype from, sizetype to);

status string_sub_from(string_t * dest, const string_t * origin, sizetype from);

status string_sub_to(string_t * dest, const string_t * origin, sizetype to);

// ----- destructor -----

void string_free(string_t * str) {
    dyna_free(str);
}

// ----- modifying -----

status string_append(string_t * str, char c) {
    status rv = dyna_set_at(str,string_length(str),&c);
    if (!rv.success)
        return rv;
    rv = dyna_append(str,&null_char);
    if (!rv.success)
        return rv;

    return OK;
}

status string_concat(string_t * left, const string_t * right) {
    status s;
    char c;
    for (sizetype i = 0; i < string_length(right); ++i) {
        string_get_at(right,i,&c);
        s = string_append(left,c);
        if (!s.success)
            return s;
    }
    return OK;
}

// ----- lookup -----

inline sizetype string_length(const string_t * str) {
    return str->length - 1; // Don't count the null termination
}

status string_get_at(const string_t * str, sizetype pos, char* c) {
    return dyna_get_at(str,pos,c);
}

sizetype string_find_first_of(const string_t * str, char c, sizetype start_pos) {
    char si;
    for (sizetype i = start_pos; i < str->length; i++) {
        dyna_get_at(str,i,&si);
        if (si == c)
            return i;
    }
    return NAN;
}

sizetype string_find_last_of(const string_t * str, char c, sizetype start_pos) {
    char si;
    for (sizetype i = str->length - 1; i >= start_pos; i--) {
        dyna_get_at(str,i,&si);
        if (si == c)
            return i;
    }
    return NAN;
}