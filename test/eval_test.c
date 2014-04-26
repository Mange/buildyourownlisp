#include <check.h>
#include "../src/parser.c"
#include "../src/eval.c"

void expect_value(char*, long);

START_TEST (eval_identity)
{
  expect_value("0", 0);
  expect_value("42", 42);
  expect_value("-42", -42);
}
END_TEST

void expect_value(char* lispy_program, long expected_value)
{
  lispy_parser* parser = create_lispy_parser();
  lispy_result* result;

  if(parse_lispy_expression(parser, "<test>", lispy_program, &result))
  {
    long value = lispy_eval_result(result);
    ck_assert_int_eq(value, expected_value);
  }
  else
  {
    char *error;
    mpc_err_print(result->mpc_result->error);
    if(asprintf(&error, "Could not parse expression \"%s\"", lispy_program))
    {
      ck_abort_msg(error);
    }
    else
    {
      ck_abort_msg("Could not parse expression, nor generate a proper error message.");
    }
    free(error);
  }
  free_lispy_parser(&parser);
}

Suite* eval_suite (void) {
  Suite* suite = suite_create("eval");

  TCase* tcase_eval = tcase_create("eval");
  tcase_add_test(tcase_eval, eval_identity);
  suite_add_tcase(suite, tcase_eval);

  return suite;
}

int main(int argc, char* argv[]) {
  int failed;
  Suite* suite = eval_suite();
  SRunner* runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failed;
}
