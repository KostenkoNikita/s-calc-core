#include "string_list.h"

void string_list_init(StringList *string_list) {
    string_list->size = 0;
    string_list->capacity = STRING_LIST_INITIAL_CAPACITY;
    string_list->data = malloc(sizeof(char*)*STRING_LIST_INITIAL_CAPACITY);
}

void string_list_append(StringList *string_list, const char* value) {
    string_list_double_capacity_if_full(string_list);
    const size_t valueLength = strlen(value);
    const int nextIndex = string_list->size++;
    string_list->data[nextIndex] = calloc((valueLength + 1), sizeof(char));
    strncpy(string_list->data[nextIndex], value, valueLength);
}

char* string_list_get(StringList *string_list, const int index) {
    if (index >= string_list->size || index < 0) {
        printf("Index %d out of bounds for token list; size: %d\n", index, string_list->size);
        return ERR_TOKEN;
    }
    return string_list->data[index];
}

void string_list_set(StringList *string_list, const int index, const char* value) {
    while (index >= string_list->size) {
        string_list_append(string_list, "\0");
    }
    const size_t valueLength = strlen(value);
    string_list->data[index] = calloc(valueLength + 1,sizeof(char));
    strncpy(string_list->data[index], value, valueLength);
}

void string_list_double_capacity_if_full(StringList *string_list) {
    if (string_list->size >= string_list->capacity) {
        string_list->capacity *= STRING_LIST_CAPACITY_MULTIPLIER;
        string_list->data = realloc(string_list->data, sizeof(char*)*string_list->capacity);
    }
}

char** string_list_export_data(StringList *string_list) {
    const int size = string_list->size;
    char** data = string_list->data;
    char** result = malloc(sizeof(char*)*size);
    for(int i = 0; i < size; i++) {
        const char* str = data[i];
        const size_t strLength = strlen(str);
        result[i] = calloc(strLength + 1, sizeof(char));
        strncpy(result[i], str, strLength);
    }
    return result;
}

void string_list_free(StringList *string_list) {
    const int size = string_list->size;
    for(int i = 0; i< size; i++) {
        free(string_list->data[i]);
    }
    free(string_list->data);
}