#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include <string.h>
#include "mpc/mpc.h"
#include "eval.h"

#define HISTORY ".frispy-history"


int main(int argc, char** argv) {
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Symbol = mpc_new("symbol");
  mpc_parser_t* Sexpr = mpc_new("sexpr");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Frispy = mpc_new("frispy");
  
  mpca_lang(MPCA_LANG_DEFAULT, 
   "                                                   \
    number   : /-?[0-9]+/;                             \
    symbol   : '+' | '-' | '*' | '/';                  \
    sexpr    : '(' <expr>* ')';                        \
    expr     : <number> | <symbol> | <sexpr>;          \
    frispy   : /^/ <expr>* /$/;                        \
   ",
    Number, Symbol, Sexpr, Expr, Frispy);
  //

  puts("Frispy version 0.1");
  puts("Press ctrl+c to exit");

  char *prompt = "frispy> ";
  char *input;

  read_history(HISTORY);
  while ((input = readline(prompt)) != NULL) {
    add_history(input);
    
    //
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Frispy, &r)) {
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
  write_history(HISTORY);

  mpc_cleanup(5, Number, Symbol, Sexpr, Expr, Frispy);
 
  return 0;
}
