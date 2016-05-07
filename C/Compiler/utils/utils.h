//
// Created by bruce on 5/7/16.
//

#ifndef LISPY_UTILS_H_H
#define LISPY_UTILS_H_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char buffer[2048];
char* readline(char* prompt) {
    fputs(prompt, stdout);
    fgets(buffer, 2048,  stdin);
    char* cpy = malloc(strlen(buffer) + 1);
    strcpy(cpy, buffer);
    cpy[strlen(cpy)-1] = '\0';
    return  cpy;
}


#endif //LISPY_UTILS_H_H
