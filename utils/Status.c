#include "Status.h"

#include <stdio.h>
#include <stdlib.h>

const status OK = {_OK,"ok","Everything went well"};
const status WARNING = {_WARNING,"warning","Usage error that has no consequence"};
const status ERROR = {_ERROR,"error","Something bad happened"};

void pedantic_assert(status s) {
    if (s.success == _OK)return;
    if (s.success)
        printf("\033[40;93;1mProgram failed with warning %s : %s\n",s.name,s.description);
    else
        printf("\033[40;91;1mProgram failed with error %s : %s\n",s.name,s.description);
    exit(EXIT_SUCCESS);
}

void strong_assert(status s) {
    if (s.success)return;
    printf("\033[40;91;1mProgram failed with error %s : %s\n",s.name,s.description);
    exit(EXIT_FAILURE);
}

void display_status(status s) {
    printf("Success : %s\nName : %s\nDescription : %s\n",(s.success ? "yes" : "no"),s.name,s.description);
}

void display_error(status s) {
    if (!s.success) {
        printf("Error\nName : %s\nDescription : %s\n",s.name,s.description);
    }
}