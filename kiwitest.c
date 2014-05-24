/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2013 KIWI.KI GmbH.
 */

/*
 * Run all tests for this project.
 */

#include "test.h"

static void handle_command_line(
  int argc, char *argv[], char **junit_xml_output_filepath)
{
  for (int i = 1; i < argc; ++i)
  {
    if (argv[i][0] == '-')
    {
      switch (argv[i][1])
      {
        case 'v':
          test_verbose = true;
          break;
        case 'f':
          if (argc > i + 1)
          {
            *junit_xml_output_filepath = argv[i + 1];
            with_color = false;
            ++i; /* Consume the file name token. */
          }
          break;
      }
    }
  }
}

/* If you provide "-v" on the command line, the test output will be more
 * verbose. If you provide a "-f" followed by a file name on the command line,
 * the test runner will output JUint-style XML to that file. */
int main(int argc, char *argv[])
{
  char *junit_xml_output_filepath = NULL;
  handle_command_line(argc, argv, &junit_xml_output_filepath);

  TEST_INIT(junit_xml_output_filepath);

  RUN_TESTS(
    test,
    test_assert_true_pass,
    test_assert_true_fail,
    test_assert_false_pass,
    test_assert_false_fail,
    test_assert_gt_gt_with_lt,
    test_assert_gt_gt,
    test_assert_gt_lt,
    test_assert_gt_eq,
    test_assert_lt_lt_with_true,
    test_assert_lt_eq_with_true,
    test_assert_lt_gt,
    test_assert_lt_lt,
    test_assert_lt_eq,
    test_assert_ge_gt,
    test_assert_ge_lt,
    test_assert_ge_eq,
    test_assert_le_gt,
    test_assert_le_lt,
    test_assert_le_eq,
    test_assert_eq_gt_with_ne,
    test_assert_eq_gt,
    test_assert_eq_lt,
    test_assert_eq_eq,
    test_assert_ne_eq_with_gt,
    test_assert_ne_gt,
    test_assert_ne_lt,
    test_assert_ne_eq,
    test_assert_string_eq_pass,
    test_assert_string_eq_fail,
    test_assert_mem_eq_pass,
    test_assert_mem_eq_fail,
    print_dashed_name_to_string_odd_name_even_len,
    print_dashed_name_to_string_odd_name_odd_len,
    print_dashed_name_to_string_even_name_even_len,
    print_dashed_name_to_string_even_name_odd_len,
    can_use_percent_in_test_assert
  );

  TEST_FINALIZE();
}
