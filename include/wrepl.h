#ifndef WREPL_H
#define WREPL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "linenoise/linenoise.h"
#include "wisp.h"
/* A quick note regarding the REPL:
    Unlike other areas of the codebase where
    we can create multiple independent objects to work
    concurrently, the REPL is one single global 
*/
void repl();

#endif