#include "parser.h"

lispy_parser* create_lispy_parser()
{
  lispy_parser* parser = malloc(sizeof(lispy_parser));
  if (parser != NULL)
  {
    parser->Number = mpc_new("number");
    parser->Operator = mpc_new("operator");
    parser->Expression = mpc_new("expression");
    parser->Lispy = mpc_new("lispy");

    mpca_lang(MPC_LANG_DEFAULT,
        " \
          number     : /-?[0-9]+/ ; \
          operator   : '+' | '-' | '*' | '/' ; \
          expression : <number> | '(' <operator> <expression>+ ')' ; \
          lispy      : /^/ <operator> <expression>+ /$/ ; \
        ",
        parser->Number, parser->Operator, parser->Expression, parser->Lispy);

    return parser;
  }
  else
  {
    return NULL;
  }
}

void free_lispy_parser(lispy_parser** parser_ref) {
  lispy_parser* parser = *parser_ref;

  mpc_cleanup(4, parser->Number, parser->Operator, parser->Expression, parser->Lispy);

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
  *result = res;

  mpc_result_t parser_result;

  if (mpc_parse(source, expression, parser->Lispy, &parser_result))
  {
    res->status = LISPY_PARSE_OK;
    return LISPY_PARSE_OK;
  }
  else
  {
    res->status = LISPY_PARSE_ERROR;
    return LISPY_PARSE_ERROR;
  }
}

void free_lispy_result(lispy_result** result)
{
  free(*result);
  *result = NULL;
}
