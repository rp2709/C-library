#include <stdio.h>

#include "DynamicArray.h"

int main() {

  dynamic_array arr;
  dyna_init(&arr, sizeof(int),&FIRST_FIT);

  for (int i = 0; i < 1000; i++) {
    dyna_append(&arr, &i);
  }

  int value;
  printf("\narray : [");
  for (int i = 0; i < arr.length; i++) {
    dyna_get_at(&arr, i, &value);
    printf("%d ", value);
  }
  printf("]\n");

  dyna_free(&arr);

  return 0;
}