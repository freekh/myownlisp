#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include "mpc/mpc.h"
#include "eval.h"

int main(int argc, char** argv) {
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Frispy = mpc_new("frispy");
  
  mpca_lang(MPCA_LANG_DEFAULT, 
   "                                                   \
    number   : /-?[0-9]+/;                             \
    operator : '+' | '-' | '*' | '/';                  \
    expr     : <number> | '(' <operator> <expr>+ ')';  \
    frispy   : /^/ <operator> <expr>+ /$/;             \
   ",
   Number, Operator, Expr, Frispy);
  //

  puts("Frispy version 0.1");
  puts("Press ctrl+c to exit");
  int finished = 0;
  while (!finished) {
    char* input = readline("frispy> ");
    add_history(input);
    
    //
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Frispy, &r)) {
      /* mpc_ast_print(r.output); */
      struct lval v = eval(r.output);
      lval_print(v);
      mpc_ast_delete(r.output);
    } else {
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }
    //
    free(input);
  }
  mpc_cleanup(4, Number, Operator, Expr, Frispy);
 
  return 0;
}
