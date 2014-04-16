#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editline/readline.h>
//#include <editline/history.h>

#include "parser.h"

int main(int argc, char** argv) {
  char* input;
  mpc_parser_t* parser = lispy_parser();
  mpc_result_t parser_result;

  puts("Lispy version 0");
  puts("Exit with ^C, ^D or \\q");

  while(1) {
    if (input != NULL) {
      free(input);
    }
    input = readline("lispy> ");
    add_history(input);

    if (input == NULL || strcmp(input, "\\q") == 0) {
      printf("\nBye!\n");
      break;
    } else {
      // TODO: Hide all of this parser stuff behind a facade
      if (mpc_parse("<stdin>", input, parser, &parser_result)) {
        mpc_ast_print(parser_result.output);
        mpc_ast_delete(parser_result.output);
      } else {
        mpc_err_print(parser_result.error);
        mpc_err_delete(parser_result.error);
      }
    }
  }
}
