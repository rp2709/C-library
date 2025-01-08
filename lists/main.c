#include <stdio.h>

#include "LinkedList.h"

int main() {

  list l;
  list_init(&l,sizeof(int),&FIRST_FIT);

  for (int i = 0; i < 50; i++) {
    list_add_front(&l, &i);
  }

  int value;

  for (list_iterator it = list_begin(&l); list_has_next(it) ; list_next(&it)) {
    list_at(it,&value);
    if (value % 2 != 0)
      list_remove(it);
  }

  for (list_iterator it = list_begin(&l); list_has_next(it); list_next(&it)) {
    list_at(it,&value);
    printf(" %d ",value);
  }

  return 0;
}