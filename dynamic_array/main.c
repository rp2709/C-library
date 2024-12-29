#include <stdio.h>

#include "DynamicArray.h"

int main() {

  dynamic_array arr;
  dyna_init(&arr, sizeof(int));
  dyna_reserve(&arr,1);

  for (int i = 0; i < 10; i++) {
    dyna_append(&arr, &i);
  }


  int value;
  printf("\narray : [");
  for (int i = 0; i < arr.length; i++) {
    dyna_at(&arr, i, &value);
    printf("%d ", value);
  }
  printf("]\n");

  return 0;
}