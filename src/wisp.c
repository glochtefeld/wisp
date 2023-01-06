#include "wisp.h"
#include <stdio.h>

const char *toktypes[] = {
    "LEFT_PAREN", "RIGHT_PAREN", "STR", "NUM", "SYM", "ERR", "EOF"
};
int main() {
    char *test = "(+ 1 (* 2 3))";
    Scanner s;
    initScanner(test, &s);

    WToken res = scanToken(&s);
    printf("Type\tAt\tLen\tLine\n");
    printf("____\t__\t___\t____\n");
    while (res.type != TOKEN_EOF) {
        printf("%s\t%lu\t%d\t%d\n", toktypes[res.type], 
        (unsigned long)&res.start - (unsigned long)&test, // line pos
        res.length, res.line);
        res = scanToken(&s);
    }

    return 0;
}