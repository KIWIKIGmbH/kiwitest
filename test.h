/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2013 KIWI.KI GmbH.
 */

/*
 * Define some macros that collectively provide the interface for using the
 * unit test harness. See the test harness unit tests (test/test_test.c) for
 * examples of how to use the unit test harness. See the main test runner for
 * this project (test/test_main.c) for an example of how to initialize the
 * harness and run tests that have been created.
 */

#ifndef TEST_H
#define TEST_H

#include "test_asserts.h"
#include "test_colors.h"
#include "junit_xml.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

/* Provide a default for KIWITEST_TIME_MEASUREMENT. */
#ifndef KIWITEST_TIME_MEASUREMENT
#define KIWITEST_TIME_MEASUREMENT 1
#endif

#if KIWITEST_TIME_MEASUREMENT
#include <time.h> // clock_t, CLOCKS_PER_SEC
#endif

#define TEST_LINE_LEN 79

extern bool test_verbose;
extern char failure_message_buffer[1024];
extern bool with_color;
extern bool silent;

#define SIZEOF_ARRAY(array) sizeof(array) / sizeof(*array)

/* Use this to define a new test function. The new function should return 0 on
 * success, or any other value for failure. The provided setup and teardown
 * functions will be called before and after the test function if they are
 * non-zero. */
#define TEST(test_name, test_setup, test_teardown) \
void test_name ## _function(void); \
struct test test_name = { \
  .setup = test_setup, \
  .teardown = test_teardown, \
  .test = test_name ## _function, \
  .name = #test_name \
}; \
void test_name ## _function(void)

/* TIME_INIT and TIME_FINALIZE will get used by TEST_INIT and TEST_FINALIZE. We
 * define them conditionally on KIWITEST_TIME_MEASUREMENT so that for platforms
 * that have no way of measuring how long tests take to run, we don't try to
 * collect or report that information. */
#if KIWITEST_TIME_MEASUREMENT
#define TIME_INIT() \
  clock_t start = clock()
#define TIME_FINALIZE() \
  clock_t end = clock(); \
  float elapsed = (float)(end - start) / CLOCKS_PER_SEC; \
  printf("Time elapsed: %0.3f seconds.\n", elapsed)
#else
#define TIME_INIT() do { } while(0)
#define TIME_FINALIZE() do { } while(0)
#endif

/* Use this to initialize the test harness. It should be used from within the
 * function where RUN_TESTS will be called. This macro should be used only once
 * within a function. */
#define TEST_INIT(junit_xml_output_filepath) \
  size_t pass_count_ = 0; \
  size_t total_tests_ran_ = 0; \
  FILE *junit_xml_file = junit_xml_init(junit_xml_output_filepath); \
  junit_xml_begin_testsuites(junit_xml_file); \
  TIME_INIT()

/* Use this to run a list of tests as a group. The provided group name serves
 * as a means for one to organize how test output is generated and does not
 * affect the running of the tests. This macro can be used multiple times
 * within a function. TEST_INIT must be used above where this macro is used. */
#define RUN_TESTS(group_name, ...) \
extern struct test __VA_ARGS__; \
struct test group_name ## test_list[] = { \
  __VA_ARGS__ \
}; \
test_runner( \
  junit_xml_file, \
  #group_name, sizeof(#group_name) - 1, \
  &pass_count_, &total_tests_ran_, \
  group_name ## test_list, SIZEOF_ARRAY(group_name ## test_list) \
)

/* Use this to present information about how the tests ran and to deinitialize
 * the test harness. It should be used within a function, below where TEST_INIT
 * is used, and also below where any RUN_TESTS are used. */
#define TEST_FINALIZE() \
  for (int i = 0; i < 79; ++i) printf("#"); \
  if (with_color) \
  { \
    printf( \
      "\n\x1b[1;%d;%dm%zu/%zu tests passed.\x1b[0m\n", \
      FOREGROUND_WHITE, \
      pass_count_ == total_tests_ran_ ? BACKGROUND_GREEN : BACKGROUND_RED, \
      pass_count_, total_tests_ran_ \
    ); \
  } \
  else \
  { \
    printf( \
      "\n%zu/%zu tests passed.\x1b[0m\n", \
      pass_count_, total_tests_ran_ \
    ); \
  } \
  junit_xml_end_testsuites(junit_xml_file); \
  junit_xml_finalize(junit_xml_file); \
  TIME_FINALIZE(); \
  return pass_count_ != total_tests_ran_

struct test {
  /* The setup and teardown functions are not allowed to fail. If you don't
   * need setup or teardown, set them to 0. */
  void (*setup)(void);
  void (*teardown)(void);

  /* Test macros will set the global 'test_passed' to false on failure, so
   * tests don't have any requirements for what they need to return */
  void (*test)(void);

  char *name;
};

/* Runs the tests, prints messages, and updates the number of passed tests and
 * total tests ran. */
void test_runner(
  FILE *junit_xml_file,
  char *group_name, size_t group_name_len,
  size_t *pass_count, size_t *total_tests_ran,
  struct test test_list[], size_t num_tests);

#endif
