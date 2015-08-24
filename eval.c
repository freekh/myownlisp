#include "eval.h"
#include <stdlib.h>
#include <stdio.h>

struct lval lval_num(long x) {
  struct lval v;
  v.type = LVAL_NUM;
  v.num = x;
  return v;
}

struct lval lval_err(int x) {
  struct lval v;
  v.type = LVAL_ERR;
  v.err = x;
  return v;
}

void lval_print_err(int err) {
  switch (err) {
  case LERR_DIV_ZERO: printf("Error: Division by Zero!"); break;
  case LERR_BAD_OP: printf("Error: Invalid operator"); break;
  case LERR_BAD_NUM: printf("Error: Invalid number"); break;
  }
}

void lval_print(struct lval v) {
  switch(v.type) {
  case LVAL_NUM: 
    printf("%li", v.num); break;
  case LVAL_ERR:
    lval_print_err(v.err);
  }
  printf("\n");
}

struct lval eval_op(struct lval x, char* op, struct lval y) {
  if (x.type == LVAL_ERR) {
    return x;
  } else if (y.type == LVAL_ERR) {
    return y;
  }

  if (strcmp(op, "*") == 0) {
    return lval_num(x.num*y.num);
  } else if (strcmp(op, "/") == 0) {
    return y.num == 0 ? lval_err(LERR_DIV_ZERO) : lval_num(x.num/y.num);
  } else if (strcmp(op, "+") == 0) {
    return lval_num(x.num+y.num);
  } else if (strcmp(op, "-") == 0) {
    return lval_num(x.num-y.num);
  } else {
    return lval_err(LERR_BAD_OP);
  }
}

struct lval eval(mpc_ast_t* t) {
  if (strstr(t->tag, "number")) {
    return lval_num(atoi(t->contents));
  }
  char *op = t->children[1]->contents;
  struct lval v = eval(t->children[2]);
  int i = 3;
  while (t->children_num > 2 && strstr(t->children[i]->tag, "expr")) {
    v = eval_op(v, op, eval(t->children[i]));
    i++;
  }
  return v;
}

