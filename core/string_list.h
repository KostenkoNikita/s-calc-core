#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LIST_INITIAL_CAPACITY 20
#define STRING_LIST_CAPACITY_MULTIPLIER 2
#define ERR_TOKEN "ERR"

typedef struct {
    int size;
    int capacity;
    char** data;
} StringList;

void string_list_init(StringList *string_list);

void string_list_append(StringList *string_list, const char* value);

char* string_list_get(StringList *string_list, int index);

void string_list_set(StringList *string_list, int index, const char* value);

void string_list_double_capacity_if_full(StringList *string_list);

void string_list_free(StringList *string_list);

char** string_list_export_data(StringList *string_list);