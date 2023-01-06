#include "wscanner.h"
#include <stdbool.h>
#include <string.h>

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
    out->start = source;
    out->current = source;
    out->line = 1;
}

static void skipWhitespace(Scanner *scanner) {
    for (;;) {
        char c = peek(scanner);
        switch (c) {
        case ';':
            while (peek(scanner) != '\n' && !isAtEnd(scanner)) {
                advance(scanner);
            }
            break;
        case '#':
            if (peekNext(scanner) == '[') {
                while (!isAtEnd(scanner)) {
                    if (peek(scanner) == '\n') scanner->line++;
                    if (peek(scanner) == ']' && peekNext(scanner) == '#') break;
                    advance(scanner);
                }
                advance(scanner); advance(scanner); // consume closing ]#
            } else {
                return;
            }
        case '\n': // Fallthrough is intentional
            scanner->line++;
        case ' ':
        case '\r':
        case '\t':
            advance(scanner);
            break;
        default:
            return;
        }
    }
}
static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}
static bool isAlpha(char c) {
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z')
        || (c == '_');
}
static bool isWhitespace(char c, char next) {
    return c == ';' || (c == '#' && next == '[')
        || c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

static WToken makeToken(Scanner *scanner, WTokenType type) {
    WToken token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int)(scanner->current - scanner->start);
    token.line = scanner->line;
    return token;
}
static WToken errorToken(Scanner *scanner, const char *message) {
    WToken token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = (int)strlen(message);
    token.line = scanner->line;
    return token;
}
static WToken string(Scanner *scanner) {
    while(peek(scanner) != '"' && !isAtEnd(scanner)) {
        if (peek(scanner) == '\n') scanner->line++;
        advance(scanner);
    }
    if (isAtEnd(scanner)) return errorToken(scanner, "Unterminated string");
    advance(scanner); // consume closing "
    return makeToken(scanner, TOKEN_STR);
}

static WToken number(Scanner *scanner) {
    if (match(scanner, '-')) advance(scanner); // consume the negation
    while (isDigit(peek(scanner))) advance(scanner);
    // mantissa
    if (peek(scanner) == '.' && isDigit(peekNext(scanner))) {
        advance(scanner); // consume the radix
        while (isDigit(peek(scanner))) advance(scanner);
    }
    return makeToken(scanner, TOKEN_NUM);
}
static WToken symbol(Scanner *scanner) {
    while(!isWhitespace(peek(scanner), peekNext(scanner))) advance(scanner);
    return makeToken(scanner, TOKEN_SYM);
}

WToken scanToken(Scanner *scanner) {
    skipWhitespace(scanner);
    scanner->start = scanner->current;
    if (isAtEnd(scanner)) return makeToken(scanner, TOKEN_EOF);

    char c = advance(scanner);
    if (isAlpha(c)) return symbol(scanner);
    if (isDigit(c)) return number(scanner);
    switch (c) {
        case '(': return makeToken(scanner, TOKEN_LEFT_PAREN);
        case ')': return makeToken(scanner, TOKEN_RIGHT_PAREN);
        case '"': return string(scanner);
        case '-':
            if (isDigit(peek(scanner))) {
                return number(scanner);
            } else {
                return symbol(scanner);
            }
        default: return symbol(scanner);
    }
}