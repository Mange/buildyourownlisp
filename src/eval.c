#include <assert.h>
#include <stdlib.h>
#include "./eval.h"

static long eval_ast(mpc_ast_t*);
static long eval_ast_root(mpc_ast_t*);
static long eval_ast_integer(mpc_ast_t*);

static long eval_ast(mpc_ast_t* ast)
{
  printf("Got AST %s: %s (%d children)\n", ast->tag, ast->contents, ast->children_num);
  if(strcmp(ast->tag, ">") == 0) { return eval_ast_root(ast); }
  if(strstr(ast->tag, "integer")) { return eval_ast_integer(ast); }

  /* See about removing this as asson as possible */
  printf("Cannot eval tag %s (%d children) \"%s\" yet.\n", ast->tag, ast->children_num, ast->contents);
  for(int i=0; i < ast->children_num; i++)
  {
    printf("Child %d: %s\n", i+1, ast->children[i]->tag);
  }
  exit(1);
}

static long eval_ast_root(mpc_ast_t* ast)
{
  // Root has three children. Regex + expression + Regex
  assert(ast->children_num == 3);
  return eval_ast(ast->children[1]);
}

static long eval_ast_integer(mpc_ast_t* ast)
{
  assert(ast->children_num == 0 || ast->children_num == 2);
  if (ast->children_num == 0)
  {
    return atoi(ast->contents);
  }
  else
  {
    // Two children means a minus sign and a normal number
    return -atoi(ast->children[1]->contents);
  }
}

long lispy_eval_result(lispy_result* result)
{
  return eval_ast(result->mpc_result->output);
}
