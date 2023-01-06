#include "wscanner.h"
#include <stdbool.h>

static bool isAtEnd(Scanner *scanner) {
    return *scanner->current == '\0';
}
static char advance(Scanner *scanner) {
    scanner->current++;
    return scanner->current[-1];
}
static char peek(Scanner *scanner) {
    return *scanner->current;
}
static char peekNext(Scanner *scanner) {
    if (isAtEnd(scanner)) return '\0';
    return scanner->current[1];
}

static bool match(Scanner *scanner, char expected) {
    if (isAtEnd(scanner)) return false;
    if (*scanner->current != expected) return false;
    scanner->current++;
    return true;
}

void initScanner(const char *source, Scanner *out) {
    out->src = source;
    out->current = source;
    out->line = 1;
}

WToken scanToken(Scanner *scanner) {
    

}