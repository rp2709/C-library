# C library

This is a personal project to learn more about implenting a variety of data structures and algorithms. However parts of this might be usefull.

You will find many commonly used data structures implemented in the most generic way possible, without using 10k macros.

## Main features
### Error management
Each function that could fail in the library will return a `status` structure. You can test for the success of a function like this : 
```C
if(fifo_push(...).sucess)
```
The `status` struct also contains a name and description, which can help debug.
Different assert functions are available

### Choice of Allocator
The structure `allocator_implementation` allows data structures that allocate memory dynamically to use different allocators seamelessly. There is currently only a wrapper for the libc standard allocator and my own first fit implementation.
First fit only works on linux (but windows and mac compability is on the todo), however my long term goal is to be able to initialize an allocator with a memory arena, and stopping it to request memory from OS.
```C
// Certain structures like dynamic arrays need an allocator
dynamic_array arr;
dyna_init(&arr,sizeof(int),&FIRST_FIT);
```
### Generic data structures
Genericity comes at a cost for certain data structures like lists and hash map where there can be A LOT of small memory allocations
- `dynamic_array`
- `stack`
- `list`
- `circular_buffer`
- `fifo`
- `hash_map`

## A final word
This is utter shit and should not be used for anything serious.
