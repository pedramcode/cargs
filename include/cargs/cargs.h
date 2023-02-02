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
void cargs_help(CargsMap_t *map, size_t map_size);
bool cargs_validate(CargsMap_t *map, size_t map_size, bool exit_on_error);
char* cargs_get(CargsMap_t *map, size_t map_size, const char* key);

#endif
