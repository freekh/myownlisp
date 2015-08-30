#ifndef SEXPR_H
#define SEXPR_H

#include "mpc/mpc.h"

struct lval {
  int type;
  long num;
  char *err;
  char *sym;
  int count;
  struct lval **cell;
};

// lval types
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR };

void lval_print(struct lval* v);
void lval_println(struct lval* v);
void lval_del(struct lval* v);
struct lval* lval_read(mpc_ast_t *t);
struct lval* lval_eval(struct lval* v);

struct lval* lval_err(char* m);
struct lval* lval_pop(struct lval* v, int i);

#endif
