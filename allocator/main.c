#include "Allocator.h"

#include <stdio.h>

int main() {
  allocator_implementation* allocator = &FIRST_FIT;

  char * buffer = allocator->malloc(12);
  if (buffer == NULL) {
    printf("Failed to allocate memory\n");
    return 1;
  }
  const char * compBuffer = "Hello World";

  for (int i = 0; i < 12; ++i) {
    buffer[i] = compBuffer[i];
  }

  printf("%s\n", buffer);

  allocator->free(buffer);

  // Torture test

  arbitrary_pointer pointers[100];
  // multiple malloc - free small chunks
  print_debug_info();
  for (int i = 0; i < 100; ++i) {
    pointers[i] = allocator->malloc(1);
  }
  print_debug_info();
  for (int i = 0; i < 100; ++i) {
    allocator->free(pointers[i]);
  }
  print_debug_info();

  // multiple malloc - free big chunks
  for (int i = 0; i < 100; ++i) {
    pointers[i] = allocator->malloc(256);
  }
  print_debug_info();
  for (int i = 0; i < 100; ++i) {
    allocator->free(pointers[i]);
  }
  print_debug_info();

  // One enormous chunk
  *pointers = allocator->malloc(5000000000);
  print_debug_info();
  allocator->free(*pointers);
  print_debug_info();

  return 0;
}
