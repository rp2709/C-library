
#include <stdlib.h>
#include <stdio.h>

#include "../utils/Status.h"
#include "Circular_Buffer.h"
#include "FIFO.h"

int main(int argc, char** argv){

    puts("\n\n Starting to test circular buffer\n");

    circular_buffer cibu;

    pedantic_assert(cibu_init(&cibu,sizeof(int)));
    pedantic_assert(cibu_reserve(&cibu,5));

    for(int i=1;i<=10;i++) {
        pedantic_assert(
          cibu_push_back(&cibu,&i)
        );
        int invert = -i;
        pedantic_assert(
            cibu_push_front(&cibu,&invert)
        );
    }

    int value;
    printf("Circular buffer : [");
    for (sizetype i = 0; i < cibu.length; ++i) {
        pedantic_assert(cibu_get_at(&cibu,i,&value));
        printf(" %d ",value);
    }
    printf("]\n");

    printf("Remove first and last elements ... \n");
    pedantic_assert(cibu_pop_back(&cibu));
    pedantic_assert(cibu_pop_front(&cibu));

    printf("Circular buffer : [");
    for (sizetype i = 0; i < cibu.length; ++i) {
        pedantic_assert(cibu_get_at(&cibu,i,&value));
        printf(" %d ",value);
    }
    printf("]\n");

    printf("\nTesting return status\n\n");

    printf("Out of bound index\n");
    display_status(cibu_get_at(&cibu,100,nullptr));

    puts("\n\n Starting to test FIFO queue\n");

    fifo queue;
    pedantic_assert(fifo_init(&queue,sizeof(int)));
    pedantic_assert(fifo_reserve(&queue,5));

    for(int i=1;i<=10;i++) {
        pedantic_assert(fifo_push(&queue,&i));
    }

    for(int i=0;i<10;i++) {
        pedantic_assert(fifo_pop(&queue,&value));
    }

    pedantic_assert(fifo_put_back(&queue,&value));

    return EXIT_SUCCESS;
}
