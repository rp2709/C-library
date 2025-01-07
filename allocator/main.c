#include "Allocator.h"

#include <stdio.h>

#define NB_ALLOCATIONS 10000

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

  arbitrary_pointer pointers[NB_ALLOCATIONS];
  // multiple malloc - free small chunks
  print_debug_info();
  for (int i = 0; i < NB_ALLOCATIONS; ++i) {
    pointers[i] = allocator->malloc(1);
  }
  print_debug_info();
  for (int i = 0; i < NB_ALLOCATIONS; ++i) {
    allocator->free(pointers[i]);
  }
  print_debug_info();

  // multiple malloc - free big chunks
  for (int i = 0; i < NB_ALLOCATIONS; ++i) {
    pointers[i] = allocator->malloc(256);
  }
  print_debug_info();
  for (int i = 0; i < NB_ALLOCATIONS; ++i) {
    allocator->free(pointers[i]);
  }
  print_debug_info();

  // One enormous chunk
  *pointers = allocator->malloc(5000000);
  print_debug_info();
  allocator->free(*pointers);
  print_debug_info();

  // - - - - - - SPEED - - - - -
#include <sys/time.h>

  struct timeval stop, start;

  gettimeofday(&start, NULL);

  for (int i = 0; i < NB_ALLOCATIONS; ++i) {
    pointers[i] = allocator->malloc(256);
  }
  for (int i = 0; i < NB_ALLOCATIONS; ++i) {
    allocator->free(pointers[i]);
  }

  gettimeofday(&stop, NULL);

  unsigned elapsed = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;

  printf("First Fit : %dus\n",elapsed);

  allocator = &STANDARD;

  gettimeofday(&start, NULL);

  for (int i = 0; i < NB_ALLOCATIONS; ++i) {
    pointers[i] = allocator->malloc(256);
  }
  for (int i = 0; i < NB_ALLOCATIONS; ++i) {
    allocator->free(pointers[i]);
  }

  gettimeofday(&stop, NULL);

  elapsed = (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec;

  printf("Standard allocator : %dus\n",elapsed);

  return 0;
}
