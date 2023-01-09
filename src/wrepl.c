#include "wrepl.h"
#include "clogger/clogger.h"

/* returns the number of unbalanced open parentheses in a line. */
static int unbalanced_parens(const char *line, int running) {
    int i = 0;
    int parens = running;
    while (line[i] != '\0') {
        if (line[i] == '(') parens++;
        else if (line[i] == ')') parens--; 
        i++;
    }
    return parens;
}

static const char *toktypes[] = {
    "LEFT_PAREN", "RIGHT_PAREN", "TOK_STRING", "TOK_NUMBER", "TOK_SYMBOL", "TOK_ERROR", "TOK_EOF"
};

static void repl_compile(const char *src) {
    Scanner s;
    initScanner(src, &s);

    WToken res = scanToken(&s);
    printf("Type\t\tAt\tLen\tLine\n");
    printf("____\t\t__\t___\t____\n");
    while (res.type != TOKEN_EOF) {
        printf("%s\t%lu\t%d\t%d\n", toktypes[res.type], 
        res.start - src, // line pos
        res.length, res.line);
        res = scanToken(&s);
    }
    printf("EOF\n");
}

void repl() {
    // Setup Linenoise
    linenoiseSetMultiLine(1);
    info_log("entered repl");

    char *line;
    while ((line = linenoise("wisp> ")) != NULL) {
        int parens = unbalanced_parens(line, 0);
        char *command = line;
        char *next;
        info_log("Initial line: %s", line);
        while (parens > 0 && (next = linenoise("> ")) != NULL) { // continue until program is balanced
            info_log("parens: %d, line: %s", parens, next);
            info_log("Reading addtl input...");
            command = strcat(command, "\n");
            command = strcat(command, next);
            parens = unbalanced_parens(next, parens);
        }
        repl_compile(command);
        linenoiseFree(command);
    }
}
