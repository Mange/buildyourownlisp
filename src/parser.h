#ifndef LISPY_PARSER_H
#define LISPY_PARSER_H 1

#include "../vendor/mpc.h"

typedef struct {
  mpc_parser_t* Decimal;
  mpc_parser_t* Integer;
  mpc_parser_t* Number;
  mpc_parser_t* Operator;
  mpc_parser_t* Expression;
  mpc_parser_t* Lispy;
} lispy_parser;

typedef enum {
  LISPY_PARSE_ERROR =  0,
  LISPY_PARSE_OK    =  1,
} lispy_parse_status;

typedef struct {
  lispy_parse_status status;
  mpc_result_t* mpc_result;
} lispy_result;

lispy_parser* create_lispy_parser();
void free_lispy_parser(lispy_parser**);

lispy_parse_status parse_lispy_expression(lispy_parser*, char*, char*, lispy_result**);
void free_lispy_result(lispy_result**);

#endif
