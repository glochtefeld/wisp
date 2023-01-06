#include "wisp.h"
#include "wrepl.h"
#include <stdio.h>

#define TESTING 0
#if TESTING
int main() {
    char *test = "(+ 1 (* 2 3))";
    char *test2 = "(- 2 1)";
    char *test3 = "(+ 3 -1)";
    Scanner s;
    initScanner(test3, &s);

    WToken res = scanToken(&s);
    printf("Type\t\tAt\tLen\tLine\n");
    printf("____\t\t__\t___\t____\n");
    while (res.type != TOKEN_EOF) {
        printf("%s\t%lu\t%d\t%d\n", toktypes[res.type], 
        res.start - test3, // line pos
        res.length, res.line);
        res = scanToken(&s);
    }
    printf("EOF\n");

    return 0;
}
#else 
int main(int argc, char **argv) {
    if (argc == 1) {
        repl();
    // } else if (argc == 2) {
        //runFile(argv[1]);
    } else {
        fprintf(stderr, "Usage: wisp [path]\n");
        exit(64);
    }
    return 0;
}
#endif
