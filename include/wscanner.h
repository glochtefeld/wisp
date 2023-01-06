#ifndef WSCANNER_H
#define WSCANNER_H

typedef enum {
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    
    TOKEN_STR, TOKEN_NUM, TOKEN_SYM,

    TOKEN_ERROR, TOKEN_EOF
} WTokenType;

typedef struct {
    WTokenType type;
    const char *start;
    int length;
    int line;
} WToken;

typedef struct {
    const char *start;
    const char *current;
    int line;
} Scanner;

void initScanner(const char *source, Scanner *scanner);
WToken scanToken(Scanner *scanner);
#endif