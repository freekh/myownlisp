#ifndef EVAL_H
#define EVAL_H

#include "mpc/mpc.h"

struct lval {
  int type;
  long num;
  int err;
};

// lval types
enum { LVAL_NUM, LVAL_ERR };

// lval errors
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };

struct lval eval(mpc_ast_t* t);
void lval_print(struct lval v);

#endif
