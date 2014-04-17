#include "parser.h"

lispy_parser* create_lispy_parser()
{
  lispy_parser* parser = malloc(sizeof(lispy_parser));
  if (parser != NULL)
  {
    parser->Decimal = mpc_new("decimal");
    parser->Integer = mpc_new("integer");
    parser->Number = mpc_new("number");
    parser->Operator = mpc_new("operator");
    parser->Expression = mpc_new("expression");
    parser->Lispy = mpc_new("lispy");

    mpca_lang(MPC_LANG_DEFAULT | MPC_LANG_WHITESPACE_SENSITIVE,
        " \
          decimal    : '-'? /([0-9]+\\.[0-9]+|\\.[0-9]+)/ ; \
          integer    : '-'? /[0-9]+/ ; \
          number     : <decimal> | <integer> ; \
          operator   : '+' | '-' | '*' | '/' ; \
          expression : <number> (' '+ <number>)+ | '(' <operator> ' '+ <expression>+ ')' ; \
          lispy      : /^/ (<operator> ' '+ <expression>+ | <number>) /$/ ; \
        ",
        parser->Decimal, parser->Integer, parser->Number, parser->Operator,
        parser->Expression, parser->Lispy);

    return parser;
  }
  else
  {
    return NULL;
  }
}

void free_lispy_parser(lispy_parser** parser_ref) {
  lispy_parser* parser = *parser_ref;

  mpc_cleanup(6, parser->Decimal, parser->Integer, parser->Number, parser->Operator, parser->Expression, parser->Lispy);

  parser->Decimal = NULL;
  parser->Integer = NULL;
  parser->Number = NULL;
  parser->Operator = NULL;
  parser->Expression = NULL;
  parser->Lispy = NULL;

  free(parser);
  *parser_ref = NULL;
}

lispy_parse_status parse_lispy_expression(lispy_parser* parser, char* source, char* expression, lispy_result** result)
{
  lispy_result *res = malloc(sizeof(lispy_result));
  mpc_result_t* parser_result = malloc(sizeof(mpc_result_t));

  *result = res;

  if (mpc_parse(source, expression, parser->Lispy, parser_result))
  {
    res->status = LISPY_PARSE_OK;
    res->mpc_result = parser_result;
    return LISPY_PARSE_OK;
  }
  else
  {
    res->status = LISPY_PARSE_ERROR;
    res->mpc_result = parser_result;
    return LISPY_PARSE_ERROR;
  }
}

void free_lispy_result(lispy_result** result)
{
  lispy_result* res = *result;

  if (res->status == LISPY_PARSE_OK)
  {
      mpc_ast_delete(res->mpc_result->output);
  }
  else
  {
      mpc_err_delete(res->mpc_result->error);
  }
  free(res);
  *result = NULL;
}
