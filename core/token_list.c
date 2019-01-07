#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token_list.h"

void token_list_init(TokenList *token_list) {
    token_list->size = 0;
    token_list->capacity = TOKEN_LIST_INITIAL_CAPACITY;
    token_list->data = malloc(sizeof(char*)*TOKEN_LIST_INITIAL_CAPACITY);
}

void token_list_append(TokenList *token_list, const char* value) {
    token_list_double_capacity_if_full(token_list);
    const size_t valueLength = strlen(value);
    const int nextIndex = token_list->size++;
    token_list->data[nextIndex] = calloc((valueLength + 1), sizeof(char));
    strncpy(token_list->data[nextIndex], value, valueLength);
}

char* token_list_get(TokenList *token_list, const int index) {
    if (index >= token_list->size || index < 0) {
        printf("Index %d out of bounds for token list; size: %d\n", index, token_list->size);
        return ERR_TOKEN;
    }
    return token_list->data[index];
}

void token_list_set(TokenList *token_list, const int index, const char* value) {
    while (index >= token_list->size) {
        token_list_append(token_list, "\0");
    }
    const size_t valueLength = strlen(value);
    token_list->data[index] = calloc(valueLength + 1,sizeof(char));
    strncpy(token_list->data[index], value, valueLength);
}

void token_list_double_capacity_if_full(TokenList *token_list) {
    if (token_list->size >= token_list->capacity) {
        token_list->capacity *= TOKEN_LIST_CAPACITY_MULTIPLIER;
        token_list->data = realloc(token_list->data, sizeof(char*)*token_list->capacity);
    }
}

void token_list_free(TokenList *token_list) {
    const int size = token_list->size;
    for(int i = 0; i< size; i++) {
        free(token_list->data[i]);
    }
    free(token_list->data);
}