#include "wscanner.h"
#include <stdbool.h>

typedef struct {
    const char *src;
    const char *current;
    int line;
} Scanner;

Scanner scanner;

static bool isAtEnd() {
    return *scanner.current == '\0';
}
static char advance() {
    scanner.current++;
    return scanner.current[-1];
}
static char peek() {
    return *scanner.current;
}
static char peekNext() {
    if (isAtEnd()) return '\0';
    return scanner.current[1];
}

static bool match(char expected) {
    if (isAtEnd()) return false;
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

void initScanner(const char *source) {

}

WToken scanToken() {

}