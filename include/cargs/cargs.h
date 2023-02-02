#ifndef CARGS_CARGS_H
#define CARGS_CARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct cargs_map {
    char *w_key;
    char c_key;
    bool required;
    char *desc;
    char *value;
} CargsMap_t;

void cargs_parse(CargsMap_t *map, size_t map_size, int argc, char **argv);

#endif
