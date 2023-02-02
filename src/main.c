#include "cargs/cargs.h"

int main(int argc, char **argv) {
    CargsMap_t map[] = {
            {"name",       'n', true,  "Name of user"},
            {"age",        'a', true,  "Age of user"},
            {"programmer", 'p', false, "Is user a programmer?"},
            {"salary",     's', false, "Salary of the user"},
    };
    size_t map_size = 4;
    cargs_parse(map, map_size, argc, argv);
    return EXIT_SUCCESS;
}