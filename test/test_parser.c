#include <check.h>
#include "../src/parsing.c"

START_TEST (parser_test)
{
  // TODO: Add some tests!
  ck_assert(1 == 1);
}
END_TEST

/* Behold my personal Cargo Cult! */

Suite* parsing_suite (void) {
  Suite* suite = suite_create("parser");
  TCase* tcase = tcase_create("case");
  tcase_add_test(tcase, parser_test);
  suite_add_tcase(suite, tcase);
  return suite;
}

int main(int argc, char* argv[]) {
  int failed;
  Suite* suite = parsing_suite();
  SRunner* runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return failed;
}
