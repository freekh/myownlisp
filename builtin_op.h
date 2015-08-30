#ifndef BUILTIN_OP_H
#define BUILTIN_OP_H

#include "sexpr.h"

struct lval* builtin_op(struct lval* v, char* op);

#endif
