#include "wsymbol.h"
#include "wscanner.h"

static void advance();
static void beginScope();
static void endScope();
static bool match(WTokenType type);
static bool check(WTokenType type);
static void consume(WTokenType type, const char *message);
static void initCompiler(WCompiler *compiler, FunctionType type);
static SExpr *endCompiler();