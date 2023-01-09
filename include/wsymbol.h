#ifndef WSYMBOL_H
#define WSYMBOL_H

#include <stdbool.h>

typedef enum {
    WOBJ_NIL,
    WOBJ_TRUE,
    WOBJ_INT,
    WOBJ_FLOAT,
    WOBJ_RAT,
} WValType;

typedef struct {
    int numerator;
    int denominator;
} WRational;

typedef struct {
    WValType type;
    union {
        bool truthy;
        WRational ratval;
        double floatval;
    } value;
} WVal;

struct WCell;
union SExpr;

typedef SExpr (*WFun)(SExpr args);

typedef struct {
    char *symbol;
    WFun *function;
    WVal value;
} WAtom;

typedef union SExpr {
    WAtom value;
    WCell cell;
} SExpr;

typedef struct WCell {
    SExpr *car;
    SExpr *cdr;
} WCell;

#endif // WSYMBOL_H