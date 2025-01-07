#include "Allocator.h"

#include <sys/mman.h>

#define PAGE_LENGTH 4096

// First fit implementation
struct __attribute__((__packed__)) chunk_info{
    struct chunk_info* next;
    struct chunk_info* prev;

    bool freed;

    uint32 size;
    arbitrary_pointer start_address[0];
} ;
typedef struct chunk_info chunk_info;

// ############### Variables #########
chunk_info* HEAD = nullptr;
sizetype TOTAL_SIZE = 0;
// ###################################

void merge_chunks(chunk_info* first, chunk_info* second) {
    // Update size
    first->size += second->size + sizeof(chunk_info);

    // Make sure HEAD isn't pointing at soon gone second
    if (second == HEAD)
        HEAD = first;

    //special case, remove only other chunk_info in list
    if (first->next == first->prev) {
        first->next = first;
        first->prev = first;
        HEAD = first;
        return;
    }

    // Update links
    first->next = second->next;
    first->next->prev = first;
}

/*
 * Merges two chunks if possible and checks if chunks are free
 */
void try_merge_chunks(chunk_info* first, chunk_info* second) {
    //chunks must be free
    if (!first->freed || !second->freed)
        return;

    //chunks must be contiguous
    if ((arbitrary_pointer)first->start_address + first->size != (arbitrary_pointer)second)
        return;

    merge_chunks(first, second);
}

chunk_info* get_chunk_info(arbitrary_pointer chunk_start) {
    return chunk_start - sizeof(chunk_info);
}

status allocate_chunk(sizetype size) {
    chunk_info* new_chunk = mmap(nullptr,size,PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE,-1,0);
    if (new_chunk == MAP_FAILED)
        return ERROR;

    TOTAL_SIZE += size;

    new_chunk->freed = true;
    new_chunk->size = size - sizeof(chunk_info);

    // Insert chunk at front of list
    // First one is a special case
    if (HEAD == nullptr) {
        new_chunk->next = new_chunk;
        new_chunk->prev = new_chunk;
        HEAD = new_chunk;
        return OK;
    }

    new_chunk->prev = HEAD->prev;
    HEAD->prev = new_chunk;

    new_chunk->prev->next = new_chunk;
    new_chunk->next = HEAD;

    // Place head on the new free chunk
    HEAD = new_chunk;

    return OK;
}

status initialize() {
    if (HEAD != nullptr)
        return WARNING;

    return allocate_chunk(PAGE_LENGTH);
}

status give_chunk(chunk_info* chunk, sizetype size) {
    if (chunk->size < size)
        return ERROR;

    chunk->freed = false;

    if (size == chunk->size || chunk->size - size < sizeof(chunk_info) + 1 )
        return OK;

    sizetype original_size = chunk->size;
    chunk->size = size;

    // we need to create a new chunk with memory leftovers
    chunk_info* new_chunk = (arbitrary_pointer)chunk->start_address + chunk->size;

    new_chunk->next = chunk->next;
    new_chunk->prev = chunk;

    chunk->next = new_chunk;
    new_chunk->next->prev = new_chunk;

    new_chunk->size = original_size - size - sizeof(chunk_info);
    new_chunk->freed = true;

    return OK;
}


arbitrary_pointer ff_malloc(sizetype size) {
    if (HEAD == nullptr) {
        status s = initialize();
        if (!s.success)
            return nullptr;
    }

    // Try to find a place with current space
    chunk_info* start = HEAD;
    do {
        // Is it suitable?
        if (!HEAD->freed || HEAD->size < size)
            continue;

        // Found one
        chunk_info* chunk_given = HEAD;
        give_chunk(chunk_given, size);
        HEAD = HEAD->next;
        return chunk_given->start_address;

    }while (HEAD != start);

    // We need to allocate more
    if (!allocate_chunk((size < TOTAL_SIZE ? TOTAL_SIZE : size)).success)
        return nullptr;

    chunk_info* chunk_given = HEAD;
    give_chunk(chunk_given, size);
    HEAD = HEAD->next;
    return chunk_given->start_address;
}

status ff_free(arbitrary_pointer ptr) {

    chunk_info* chunk = get_chunk_info(ptr);
    chunk->freed = true;

    try_merge_chunks(chunk, chunk->next);
    try_merge_chunks(chunk->prev, chunk);

    return OK;
}

status ff_reallocate(arbitrary_pointer* ptr, sizetype size) {
    // reallocate on nullptr simply calls malloc
    if (*ptr == nullptr) {
        *ptr = ff_malloc(size);
        return (*ptr == nullptr) ? ERROR : OK;
    }

    chunk_info* chunk = get_chunk_info(*ptr);

    if (size < chunk->size)
        return ERROR;

    // Check if we can merge with the next one
    if (chunk->next->freed && (arbitrary_pointer)chunk->start_address + chunk->size == (arbitrary_pointer)chunk->next) {
        merge_chunks(chunk, chunk->next);
        give_chunk(chunk, size);
        return OK;
    }

    // Nope, let's malloc and copy over
    arbitrary_pointer new_ptr = ff_malloc(size);
    if (new_ptr == nullptr)
        return ERROR;

    memcopy(ptr, new_ptr, chunk->size);

    ff_free(chunk->start_address);

    *ptr = new_ptr;

    return OK;
}

allocator_implementation FIRST_FIT = {
    ff_malloc,
    ff_free,
    ff_reallocate
};


// ########## DEBUG ############

#include <stdio.h>
void print_debug_info() {
    sizetype size_count = 0,chunk_count = 0;
    chunk_info* start = HEAD;
    printf("\n[ ");
    do {
        printf("%d ", HEAD->size);
        size_count += HEAD->size + sizeof(chunk_info);
        chunk_count++;

        HEAD = HEAD->next;
    }while (HEAD != start);
    printf("]\n");

    printf("Expected size : %ld\nReal size : %ld\n\n",TOTAL_SIZE,size_count);

    printf("Chunk count : %ld\n\n",chunk_count);
}