#include <check.h>
#include "../src/parser.c"

void expect_parsing_ok(lispy_parser*, char*);
void expect_parse_error(lispy_parser*, char*);

START_TEST (api_freeing_sets_pointer_to_null)
{
  lispy_parser* parser = create_lispy_parser();
  free_lispy_parser(&parser);
  ck_assert_msg(parser == NULL, "Parser variable is not set to NULL after freeing");
}
END_TEST

START_TEST (api_parsing_results)
{
  lispy_parser* parser = create_lispy_parser();
  lispy_result* result;

  if (parse_lispy_expression(parser, "<test>", "42", &result) != LISPY_PARSE_OK)
  {
    ck_abort_msg("Parsing failed.");
  }

  ck_assert_msg(result->status == LISPY_PARSE_OK, "Status is not set to LISPY_PARSER_OK");

  free_lispy_result(&result);
  ck_assert_msg(result == NULL, "Result variable is not set to NULL after freeing");

  free_lispy_parser(&parser);
}
END_TEST

START_TEST (api_parsing_bad_results)
{
  lispy_parser* parser = create_lispy_parser();
  lispy_result* result;

  if (parse_lispy_expression(parser, "<test>", "i love u", &result) != LISPY_PARSE_ERROR)
  {
    ck_abort_msg("Parsing did not fail, like it was supposed to.");
  }

  ck_assert_msg(result->status == LISPY_PARSE_ERROR, "Status is not set to LISPY_PARSER_ERROR");

  free_lispy_result(&result);
  free_lispy_parser(&parser);
}
END_TEST

START_TEST (grammar_simple_expressions)
{
  lispy_parser* parser = create_lispy_parser();
  expect_parsing_ok(parser, "99");
  expect_parsing_ok(parser, "-1");
  expect_parsing_ok(parser, "+ 99 1");
  expect_parsing_ok(parser, "* 1 1 2 3 5 8");

  expect_parse_error(parser, "+");
  expect_parse_error(parser, "");
  expect_parse_error(parser, "1 2 3");
  free_lispy_parser(&parser);
}
END_TEST

START_TEST (grammar_decimal_numbers)
{
  lispy_parser* parser = create_lispy_parser();
  expect_parsing_ok(parser, "1.2");
  expect_parsing_ok(parser, ".2");
  expect_parsing_ok(parser, "0.0001");
  expect_parsing_ok(parser, "9999.0001");
  expect_parsing_ok(parser, "-1.0");
  expect_parsing_ok(parser, "0.0");
  expect_parsing_ok(parser, ".0");
  expect_parsing_ok(parser, "-.0");

  expect_parse_error(parser, "-");
  expect_parse_error(parser, ".");
  expect_parse_error(parser, "--1");
  expect_parse_error(parser, "1.1.2");
  expect_parse_error(parser, "1.-1");
  expect_parse_error(parser, "1.");
  free_lispy_parser(&parser);
}
END_TEST

void expect_parsing_ok(lispy_parser* parser, char* input) {
  lispy_result* result;

  if(!parse_lispy_expression(parser, "<test>", input, &result))
  {
    char *error;
    mpc_err_print(result->mpc_result->error);
    if(asprintf(&error, "Could not parse expression \"%s\"", input))
    {
      ck_abort_msg(error);
    }
    else
    {
      ck_abort_msg("Could not parse expression, nor generate a proper error message.");
    }
    free(error);
  }

  free_lispy_result(&result);
}

void expect_parse_error(lispy_parser* parser, char* input) {
  lispy_result* result;

  if(parse_lispy_expression(parser, "<test>", input, &result))
  {
    char *error;
    mpc_ast_print(result->mpc_result->output);

    if(asprintf(&error, "Expected expression \"%s\" to give parse error.", input))
    {
      ck_abort_msg(error);
    }
    else
    {
      ck_abort_msg("Could parse expression, but not generate a proper error message.");
    }
    free(error);
  }

  free_lispy_result(&result);
}

Suite* parser_suite (void) {
  Suite* suite = suite_create("parser");

  TCase* tcase_api = tcase_create("API");
  tcase_add_test(tcase_api, api_freeing_sets_pointer_to_null);
  tcase_add_test(tcase_api, api_parsing_results);
  tcase_add_test(tcase_api, api_parsing_bad_results);
  suite_add_tcase(suite, tcase_api);

  TCase* tcase_grammar = tcase_create("Grammar");
  tcase_add_test(tcase_grammar, grammar_simple_expressions);
  tcase_add_test(tcase_grammar, grammar_decimal_numbers);
  suite_add_tcase(suite, tcase_grammar);

  return suite;
}

int main(int argc, char* argv[]) {
  int failed;
  Suite* suite = parser_suite();
  SRunner* runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failed;
}
