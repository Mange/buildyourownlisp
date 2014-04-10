#ifndef LISPY_PARSING_H
#define LISPY_PARSING_H 1

#include "../vendor/mpc.h"

mpc_parser_t* lispy_parser();
void cleanup_lispy_parser();

#endif
