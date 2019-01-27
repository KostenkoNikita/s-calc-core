#pragma once

#include "token.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define TOKEN_QUEUE_INITIAL_CAPACITY 10
#define TOKEN_QUEUE_CAPACITY_MULTIPLIER 2

typedef struct {
    unsigned int size;
    unsigned int capacity;
    int front;
    int back;
    Token** data;
} TokenQueue;

TokenQueue* initTokenQueue();

bool isTokenQueueEmpty(const TokenQueue* qp);

void tokenQueueEnqueue(TokenQueue* qp, Token* tp);

Token* tokenQueueDequeue(TokenQueue* qp);

Token* tokenQueuePeek(const TokenQueue* qp);

void tokenQueueClear(TokenQueue* qp);

void freeTokenQueue(TokenQueue* qp);