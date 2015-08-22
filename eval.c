#include "eval.h"
#include <stdlib.h>
#include <stdio.h>


long eval_op(long x, char* op, long y) {
  if (strcmp(op, "*") == 0) {
    return x*y;
  } else if (strcmp(op, "/") == 0) {
    return x/y;
  } else if (strcmp(op, "+") == 0) {
    return x+y;
  } else if (strcmp(op, "-") == 0) {
    return x-y;
  } else {
    printf("CATASTOPHIC ERROR: unknown op: %s", op);
    return -1;
  }
}

long eval(mpc_ast_t* t) {
  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }
  char* op = t->children[1]->contents;
  long x = eval(t->children[2]);
  int i = 3;
  while (t->children_num > 2 && strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }
  return x;
}
