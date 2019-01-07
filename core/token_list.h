#pragma once

#define TOKEN_LIST_INITIAL_CAPACITY 20
#define TOKEN_LIST_CAPACITY_MULTIPLIER 2
#define ERR_TOKEN "ERR"

typedef struct {
    int size;
    int capacity;
    char** data;
} TokenList;

void token_list_init(TokenList *token_list);

void token_list_append(TokenList *token_list, const char* value);

char* token_list_get(TokenList *token_list, int index);

void token_list_set(TokenList *token_list, int index, const char* value);

void token_list_double_capacity_if_full(TokenList *token_list);

void token_list_free(TokenList *token_list);