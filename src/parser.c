#include "parser.h"

static mpc_parser_t* Number;
static mpc_parser_t* Operator;
static mpc_parser_t* Expression;
static mpc_parser_t* Lispy;

static short parser_is_set_up = 0;

mpc_parser_t* lispy_parser() {
  if (parser_is_set_up) {
    return Lispy;
  }

  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expression = mpc_new("expression");
  mpc_parser_t* Lispy = mpc_new("lispy");

  mpca_lang(MPC_LANG_DEFAULT,
      " \
        number     : /-?[0-9]+/ ; \
        operator   : '+' | '-' | '*' | '/' ; \
        expression : <number> | '(' <operator> <expression>+ ')' ; \
        lispy      : /^/ <operator> <expression>+ /$/ ; \
      ",
      Number, Operator, Expression, Lispy);

  parser_is_set_up = 1;
  return Lispy;
}

void cleanup_lispy_parser() {
  mpc_cleanup(4, Number, Operator, Expression, Lispy);

  Number = NULL;
  Operator = NULL;
  Expression = NULL;
  Lispy = NULL;

  parser_is_set_up = 0;
}
