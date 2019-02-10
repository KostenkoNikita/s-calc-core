#include <stdio.h>
#include "rpn_writer/rpn_writer.h"
#include "common/token_stack.h"
#include "common/token_queue.h"
#include "common/token.h"

int main() {
    TokenQueue* q = initTokenQueue();
    TokenStack* s = initTokenStack();
    writeRpn("3+4", s, q);
    while(!isTokenQueueEmpty(q)) {
        const Token* t = tokenQueueDequeue(q);
        printf("%s ", t->tokenString);
    }
    printf("\n");
    freeTokenQueue(q);
    freeTokenStack(s);
    return 0;
}