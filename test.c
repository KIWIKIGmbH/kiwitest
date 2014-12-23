/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2013 KIWI.KI GmbH.
 */

#include "test.h"
#include "junit_xml.h"
#include <stdio.h>
#include <stdbool.h>
#include <setjmp.h>

bool test_verbose = false;
char failure_message_buffer[1024];
bool with_color = true;
bool silent = false;
jmp_buf test_runner_env;

/*
 * Print out the provided name to the provided string, centered on a line
 * filled with dashes of length line_len.
 *
 * For example, if line_len is 15 and name is "hello", it would fill s with:
 * "---- hello ----"
 *
 * Note that this function isn't meant to be used externally, but it is
 * non-static so that the test harness unit tests can test it.
 */
void print_dashed_name_to_string(
  char *s, const char *name, const size_t name_len, const size_t line_len)
{
  size_t name_start = line_len / 2 - name_len / 2;
  /* We increment name_len by 1 here so that for odd name lengths, no
   * dimensional data is lost due to integer division. */
  size_t name_end = line_len / 2 + (name_len + 1) / 2;

  for (size_t i = 0; i < line_len; ++i)
  {
    if ((i >= name_start) && (i < name_end))
    {
      /* Since we are where the name will go, fill the string with the name. */
      *s++ = name[i - name_start];
    }
    else if ((i == name_start - 1) || (i == name_end))
    {
      /* Since we are around where the name will go, fill the string with
       * spaces. */
      *s++ = ' ';
    }
    else
    {
      /* Fill the string with dashes. */
      *s++ = '-';
    }
  }

  /* NUL-terminate the string. */
  *s = '\0';
}

static void print_dashed_name(
  const char *name, const size_t name_len, const size_t line_len)
{
  char line[120];
  print_dashed_name_to_string(line, name, name_len, line_len);
  printf("%s\n", line);
}

void test_runner(
  FILE *junit_xml_file,
  char *group_name, size_t group_name_len,
  size_t *pass_count, size_t *total_tests_ran,
  struct test test_list[], size_t num_tests)
{
  /* Keep track of the number of tests passed so that we can present
   * information about how many tests passed. */
  size_t runner_pass_count = 0;

  junit_xml_begin_testsuite(junit_xml_file, group_name, num_tests);

  print_dashed_name(group_name, group_name_len, TEST_LINE_LEN);

  /* Run all the tests, printing out information about how things are going
   * along the way. */
  for (size_t i = 0; i < num_tests; ++i)
  {
    /* Run the test setup function, if it exists. */
    if (test_list[i].setup) test_list[i].setup();

    /* Print the name of the test now, just in case it hangs. This isn't
     * colored because we don't know if it will pass or fail yet. When it does
     * pass or fail, we'll print a '\r' to "erase" the non-colored print and
     * write over it with colored print. */
    printf("%s:", test_list[i].name);

#if KIWITEST_TIME_MEASUREMENT
    clock_t start = clock();
#endif

    int failed = false;

    /* Set a failure handler. */
    if (setjmp(test_runner_env))
    {
      /* If setjmp is non-zero, then we got here from a longjmp (which only
       * happens when tests fail). */
      failed = true;
    }
    else
    {
      /* The test didn't run yet, so run it. */
      test_list[i].test();
    }

#if KIWITEST_TIME_MEASUREMENT
    int ticks_elapsed = clock() - start;
    float elapsed_time = ticks_elapsed / CLOCKS_PER_SEC;
#else
    float elapsed_time = 0;
#endif

    if (failed)
    {
      /* Display a detailed fail message for the failing test. */
      printf(
        "\r\x1b[1;%d;%dm%s:[%s]\x1b[0m\n\n",
        FOREGROUND_WHITE, BACKGROUND_RED,
        test_list[i].name, "FAIL"
      );

      junit_xml_fail_testcase(
        junit_xml_file,
        group_name, test_list[i].name, elapsed_time,
        failure_message_buffer
      );
    }
    else
    {
      if (test_verbose)
      {
        /* Display a detailed pass message for the passing test. */
        printf(
          "\r\x1b[1;%d;%dm%s:[%s]\x1b[0m\n\n",
          FOREGROUND_WHITE, failed ? BACKGROUND_RED : BACKGROUND_GREEN,
          test_list[i].name, "PASS"
        );
      }

      /* Clear the line. Since we emitted some non-colored print for this test,
       * but we don't want to display very much print when not in verbose mode,
       * we need to erase the non-colored print. We do so by setting the cursor
       * to the start of the line and emitting spaces and resetting the cursor
       * back again. */
      printf("\r");
      for (int i = 0; i < TEST_LINE_LEN; ++i) printf(" ");
      printf("\r");

      junit_xml_pass_testcase(
        junit_xml_file, group_name, test_list[i].name, elapsed_time
      );
    }

    if (!failed) ++runner_pass_count;

    /* Run the test teardown function, if it exists. */
    if (test_list[i].teardown) test_list[i].teardown();
  }

  /* All tests have finished running, so display a summary of what happened. */
  if (with_color)
  {
    printf(
      "\r\x1b[1;%d;%dm%zu/%zu %s tests passed.\x1b[0m\n\n",
      FOREGROUND_WHITE,
      runner_pass_count == num_tests ? BACKGROUND_GREEN : BACKGROUND_RED,
      runner_pass_count, num_tests,
      group_name
    );
  }
  else
  {
    printf(
      "\r%zu/%zu %s tests passed.\n\n",
      runner_pass_count, num_tests,
      group_name
    );
  }

  junit_xml_end_testsuite(junit_xml_file);

  *pass_count += runner_pass_count;
  *total_tests_ran += num_tests;
}
