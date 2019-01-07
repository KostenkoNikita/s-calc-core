#pragma once

#include "token_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TMP_TOKENIZER_STRING_INITIAL_CAPACITY 10
#define TMP_TOKENIZER_STRING_CAPACITY_MULTIPLIER 2

#define TMP_FACTORIAL_STRING_INITIAL_CAPACITY 3

#define SUCCESS_RETURN_CODE 0
#define UNDEFINED_CHAR_ERR_CODE 1

#define IS_BRACKET(c) (c == '(' || c == ')')
#define IS_PLUS_OR_MINUS(c) (c == '+' || c == '-')
#define IS_OPERATOR(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c=='%')
#define IS_FACTORIAL(c) (c == '!')
#define IS_SEPARATOR(c) (c == ',')
#define IS_DOT(c) (c == '.')
#define IS_DIGIT_OR_DOT(c) (isdigit(c) || IS_DOT(c))
#define IS_EXPONENT(c) (c == 'e' || c == 'E')
#define IS_WHITESPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')

int tokenize(const char* s, TokenList* l);

void check_string_length_and_extend(char** str, size_t* size, int index);
