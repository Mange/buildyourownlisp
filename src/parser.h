#ifndef LISPY_PARSER_H
#define LISPY_PARSER_H 1

#include "../vendor/mpc.h"

mpc_parser_t* lispy_parser();
void cleanup_lispy_parser();

#endif
