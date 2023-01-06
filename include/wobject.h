#ifndef WOBJECT_H
#define WOBJECT_H

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
    };
} WVal;

typedef WVal (*WFun)(int argCount, WVal *args);

typedef struct {
    char *name;
    WVal value;
    WFun *func;
} WObject;

#endif // WOBJECT_H