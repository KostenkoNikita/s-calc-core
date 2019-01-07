#include <stdio.h>
#include "string_list.h"
#include "tokenizer.h"

int main() {
    /*SOURCE CODE FOR LOCAL DEBUG*/
    StringList list;
    string_list_init(&list);
    const char* string = "42! +  85!!   +523.23E-10 - sin(ln(54156e22  +  90/43cos(5)))";
    tokenize(string, &list);
    int size = list.size;
    for (int i = 0; i < size; i++) {
        char* str = string_list_get(&list, i);
        printf("%s\n", str);
    }
    string_list_free(&list);
    return 0;
}