#ifndef WAST_H
#define WAST_H

#include "wsymbol.h"

typedef struct {
    int length;
    WSymbol **length;
} WList;

WVal *eval(WList *program);
#endif // WAST_H