#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum cargs_type {
    INT = 0,
    DOUBLE = 1,
    STRING = 2,
    BOOLEAN = 3,
} CargsType;

typedef struct cargs_map {
    char *w_key;
    char c_key;
    CargsType type;
    bool required;
    char *desc;
    char *value;
} CargsMap_t;


bool is_word_key(const char *key) {
    return strlen(key) > 2 && key[0] == '-' && key[1] == '-';
}

bool is_char_key(const char *key) {
    return strlen(key) == 2 && key[0] == '-' && key[1] != '-';
}

int main(int argc, char **argv) {
    CargsMap_t map[] = {
            {"name",       'n', STRING,  true,  "Name of user"},
            {"age",        'a', INT,     true,  "Age of user"},
            {"programmer", 'p', BOOLEAN, false, "Is user a programmer?"},
            {"salary",     's', DOUBLE,  false, "Salary of the user"},
    };
    size_t map_size = 4;

    CargsMap_t *current = NULL;
    for (int i = 0; i < argc; i++) {
        char *key = argv[i];
        if (is_word_key(key)) {
            char *key_raw = (char *) malloc((sizeof(char) * (strlen(key) - 2)) + 1);
            strncpy(key_raw, &key[2], strlen(key) - 2);
            key_raw[strlen(key) - 2] = '\0';
            for (int j = 0; j < map_size; j++) {
                if (key == map[j].w_key) {
                    current = &map[j];
                    break;
                }
            }
        } else if (is_char_key(key)) {
            char *key_raw = (char *) malloc((sizeof(char) * (strlen(key) - 1)) + 1);
            strncpy(key_raw, &key[1], strlen(key) - 1);
            key_raw[strlen(key) - 1] = '\0';
            for (int j = 0; j < map_size; j++) {
                if (key[0] == map[j].c_key) {
                    current = &map[j];
                    break;
                }
            }
        }

        if (current != NULL) {
            current->value = (char *) malloc(sizeof(char) * strlen(argv[i + 1]));
            strcpy(current->value, argv[i+1]);
        }
    }

    for (int i = 0; i < map_size; i++) {
        printf("%s %c %s\n", map[i].w_key, map[i].c_key, map[i].value);
    }
    return EXIT_SUCCESS;
}