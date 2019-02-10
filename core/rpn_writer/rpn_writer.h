#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../common/string_list.h"
#include "../status/status.h"
#include "../common/token.h"
#include "../common/token_queue.h"
#include "../common/token_stack.h"
#include "../math/functions.h"

#define TMP_TOKENIZER_STRING_INITIAL_CAPACITY 10
#define TMP_TOKENIZER_STRING_CAPACITY_MULTIPLIER 2

#define TMP_FACTORIAL_STRING_INITIAL_CAPACITY 3

#define IS_DIGIT(c) (isdigit(c))
#define IS_OPENING_BRACKET(c) (c == '(')
#define IS_CLOSING_BRACKET(c) (c == ')')
#define IS_PLUS_OR_MINUS(c) (c == '+' || c == '-')
#define IS_FACTORIAL(c) (c == '!')
#define IS_OPERATOR(c) (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c=='%' || IS_FACTORIAL(c))
#define IS_SEPARATOR(c) (c == ',')
#define IS_DOT(c) (c == '.')
#define IS_DIGIT_OR_DOT(c) (IS_DIGIT(c) || IS_DOT(c))
#define IS_EXPONENT(c) (c == 'e' || c == 'E')
#define IS_WHITESPACE(c) (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')

SCalcCoreStatus tokenize(const char* s, StringList* l);

SCalcCoreStatus writeRpn(const char* str, TokenStack* s, TokenQueue* q);

void checkStringLengthAndExtend(char **str, size_t *size, int index);

char* processAlphaChar(const char **str_p, int *currStrIndex);

char* processFactorial(const char **str_p, int *currStrIndex);

char* processDigit(const char **str_p, int *currStrIndex);
