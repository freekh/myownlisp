#include "builtin_op.h"

struct lval* builtin_op(struct lval* v, char* op) {
  for (int i = 0; i < v->count; i++) {
    if (v->cell[i]->type != LVAL_NUM) {
      lval_del(v);
      return lval_err("cannot operate on non-number");
    }
  }
  
  struct lval* x = lval_pop(v, 0);

  if ((strcmp(op, "-") == 0) && v->count == 0) {
    x->num = -x->num;
  }
  
  while (v->count > 0) {
    struct lval* y = lval_pop(v, 0);

    if (strcmp(op, "+") == 0) { x->num += y->num; }
    if (strcmp(op, "-") == 0) { x->num -= y->num; }
    if (strcmp(op, "*") == 0) { x->num *= y->num; }
    if (strcmp(op, "/") == 0) {
      if (y->num == 0) {
        lval_del(x); lval_del(y);
        x = lval_err("division by zero!"); break;
      }
      x->num /= y->num;
    }

    lval_del(y);
  }
  lval_del(v); return x;
}
