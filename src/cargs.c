#include "cargs.h"

bool is_word_key(const char *key) {
    return strlen(key) > 2 && key[0] == '-' && key[1] == '-';
}

bool is_char_key(const char *key) {
    return strlen(key) == 2 && key[0] == '-' && key[1] != '-';
}

void cargs_parse(CargsMap_t *map, size_t map_size, int argc, char **argv){

    if(argc == 2 && strcmp(argv[1], "help")==0){
        cargs_help(map, map_size);
        return;
    }

    CargsMap_t **current = (CargsMap_t **) malloc(sizeof(CargsMap_t *));
    if ((argc - 1) % 2 != 0) {
        fprintf(stderr, "Invalid input\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i += 2) {
        char *key = argv[i];

        if (is_word_key(key)) {
            char *key_raw = (char *) malloc((sizeof(char) * (strlen(key) - 2)) + 1);
            strncpy(key_raw, &key[2], strlen(key) - 2);
            key_raw[strlen(key) - 2] = '\0';
            for (int j = 0; j < map_size; j++) {
                if (strcmp(key_raw, map[j].w_key) == 0) {
                    *current = &map[j];
                    break;
                }
            }
        } else if (is_char_key(key)) {
            char *key_raw = (char *) malloc((sizeof(char) * (strlen(key) - 1)) + 1);
            strncpy(key_raw, &key[1], strlen(key) - 1);
            key_raw[strlen(key) - 1] = '\0';
            for (int j = 0; j < map_size; j++) {
                if (key_raw[0] == map[j].c_key) {
                    *current = &map[j];
                    break;
                }
            }
        }

        if (*current != NULL) {
            if (is_word_key(argv[i + 1]) || is_char_key(argv[i + 1])) {
                fprintf(stderr, "\"%s\": Invalid value\n", argv[i]);
                exit(EXIT_FAILURE);
            }
            (*current)->value = (char *) malloc(sizeof(char) * strlen(argv[i + 1]));
            strcpy((*current)->value, argv[i + 1]);
            free(current);
        } else {
            fprintf(stderr, "Invalid key: \"%s\"\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }
}

bool cargs_validate(CargsMap_t *map, size_t map_size, bool exit_on_error){
    bool error = false;
    for (int i = 0; i < map_size; i++) {
        if (map[i].value == NULL && map[i].required == true) {
            fprintf(stderr, "\"%s\" argument is required\n", map[i].w_key);
            error = true;
        }
    }
    if (exit_on_error && error) {
        exit(EXIT_FAILURE);
    }
    return error;
}

void cargs_help(CargsMap_t *map, size_t map_size){
    for (int i = 0; i < map_size; i++) {
        if (map[i].value == NULL && map[i].required == true) {
            fprintf(stdout, "-%c\t--%s\t%s\n", map[i].c_key, map[i].w_key, map[i].desc);
        }
    }
}

char* cargs_get(CargsMap_t *map, size_t map_size, const char* key){
    for (int i = 0; i < map_size; i++) {
        if (map[i].w_key == key) {
            return map[i].value;
        }
    }
    return NULL;
}