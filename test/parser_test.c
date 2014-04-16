#include <check.h>
#include "../src/parser.c"

START_TEST (api_freeing_sets_pointer_to_null)
{
  lispy_parser* parser = create_lispy_parser();
  free_lispy_parser(&parser);
  ck_assert_msg(parser == NULL, "Parser variable is not set to NULL after freeing");
}
END_TEST

START_TEST (grammar_simple_expressions)
{
  lispy_parser* parser = create_lispy_parser();
  lispy_result* result;
  lispy_parse_status parse_status;

  parse_status = parse_lispy_expression(parser, "<test>", "+ 1 2", &result);
  if (parse_status == LISPY_PARSE_ERROR)
  {
    ck_abort_msg("Could not parse expression \"+ 1 2\"");
  }
  else if (parse_status == LISPY_PARSE_FAIL)
  {
    ck_abort_msg("Parsing failed");
  }

  free_lispy_result(&result);
  free_lispy_parser(&parser);
}
END_TEST

START_TEST (grammar_bad_expressions)
{
  lispy_parser* parser = create_lispy_parser();
  lispy_result* result;
  lispy_parse_status parse_status;

  parse_status = parse_lispy_expression(parser, "<test>", "i love u", &result);
  if (parse_status == LISPY_PARSE_FAIL)
  {
    ck_abort_msg("Parsing failed");
  }
  else if (parse_status == LISPY_PARSE_OK)
  {
    ck_abort_msg("Successfully parsed bad expression \"i love u\"");
  }

  free_lispy_result(&result);
  free_lispy_parser(&parser);
}
END_TEST

Suite* parser_suite (void) {
  Suite* suite = suite_create("parser");

  TCase* tcase_api = tcase_create("API");
  tcase_add_test(tcase_api, api_freeing_sets_pointer_to_null);
  suite_add_tcase(suite, tcase_api);

  TCase* tcase_grammar = tcase_create("Grammar");
  tcase_add_test(tcase_grammar, grammar_simple_expressions);
  tcase_add_test(tcase_grammar, grammar_bad_expressions);
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
