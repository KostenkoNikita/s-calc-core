#include "token_queue.h"

TokenQueue* initTokenQueue() {
    TokenQueue* qp = (TokenQueue*)malloc(sizeof(TokenQueue));
    qp->capacity = TOKEN_QUEUE_INITIAL_CAPACITY;
    qp->front = qp->size = 0;
    qp->back = qp->capacity - 1;
    qp->data = (Token**)malloc(qp->capacity * sizeof(Token*));
    return qp;
}

bool isTokenQueueEmpty(const TokenQueue* qp) {
    return qp->size == 0;
}

void tokenQueueEnqueue(TokenQueue* qp, Token* tp) {
    if(qp->size == qp->capacity) {
        qp->capacity += TOKEN_QUEUE_CAPACITY_MULTIPLIER;
        qp->data = (Token**)realloc(qp->data, qp->capacity * sizeof(Token*));
    }
    qp->back = (qp->back + 1) % qp->capacity;
    qp->data[qp->back] = tp;
    qp->size++;
}

Token* tokenQueueDequeue(TokenQueue* qp) {
    if(isTokenQueueEmpty(qp)) {
        return NULL;
    }
    Token* tp = qp->data[qp->front];
    qp->front = (qp->front + 1) % qp->capacity;
    qp->size--;
    return tp;
}

Token* tokenQueuePeek(const TokenQueue* qp) {
    if(isTokenQueueEmpty(qp)) {
        return NULL;
    }
    return qp->data[qp->front];
}

void tokenQueueClear(TokenQueue* qp) {
    while(!isTokenQueueEmpty(qp)) {
        Token* tp = tokenQueueDequeue(qp);
        freeToken(tp);
    }
}

void freeTokenQueue(TokenQueue* qp) {
    tokenQueueClear(qp);
    free(qp->data);
    free(qp);
}