/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2013 KIWI.KI GmbH.
 */

/*
 * This file contains tests for the unit test harness that use the unit test
 * harness.
 */

#include "test.h"

/* This comes from test/test.c. */
extern void print_dashed_name_to_string(
  char *s, const char *name, const size_t name_len, const size_t line_len
);

static void mute_stdout(void)
{
  silent = true;
}

static void unmute_stdout(void)
{
  silent = false;
}

static int test_true(int condition)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    /* Run the test. */
    TEST_TRUE(condition);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  /* Pass */
  return failed;
}

static int test_false(int condition)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_FALSE(condition);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  return failed;
}

static int test_gt(int a, int b)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_GT(a, b);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  return failed;
}

static int test_lt(int a, int b)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_LT(a, b);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  /* Pass */
  return failed;
}

static int test_ge(int a, int b)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_GE(a, b);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  return failed;
}

static int test_le(int a, int b)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_LE(a, b);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  return failed;
}

static int test_eq(int a, int b)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_EQ(a, b);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  return failed;
}

static int test_ne(int a, int b)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_NE(a, b);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  return failed;
}

static int test_string_eq(char *a, char *b)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_STRING_EQ(a, b);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  return failed;
}

static int test_mem_eq(void *a, void *b, size_t n)
{
  int failed = 0;
  /* Override the default failure handler. */
  jmp_buf previous_test_runner_env;
  memcpy(previous_test_runner_env, test_runner_env, sizeof(test_runner_env));
  if (setjmp(test_runner_env))
  {
    failed = 1;
  }
  else
  {
    TEST_MEM_EQ(a, b, n);
  }

  /* Restore the default failure handler. */
  memcpy(test_runner_env, previous_test_runner_env, sizeof(test_runner_env));

  return failed;
}

TEST(test_assert_true_pass, 0, 0)
{
  int a = 1;
  /* While testing the test, disable stdout. */
  mute_stdout();
  int result = test_true(a);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_true_fail, 0, 0)
{
  int a = 0;
  mute_stdout();
  int result = test_true(a);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_false_pass, 0, 0)
{
  int a = 0;
  mute_stdout();
  int result = test_false(a);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_false_fail, 0, 0)
{
  int a = 1;
  mute_stdout();
  int result = test_false(a);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_gt_gt_with_lt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_gt(a, b);
  unmute_stdout();

  TEST_LT(result, 1);
}

TEST(test_assert_gt_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_gt(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_gt_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_gt(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_gt_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_gt(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_lt_lt_with_true, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_TRUE(result == 0);
}

TEST(test_assert_lt_eq_with_true, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_TRUE(result == 1);
}

TEST(test_assert_lt_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_lt_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_lt_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_ge_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_ge(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_ge_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_ge(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_ge_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_ge(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_le_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_le(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_le_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_le(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_le_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_le(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_eq_gt_with_ne, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_eq(a, b);
  unmute_stdout();

  TEST_NE(result, 0);
}

TEST(test_assert_eq_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_eq(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_eq_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_eq(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_eq_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_eq(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_ne_eq_with_gt, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_ne(a, b);
  unmute_stdout();

  TEST_GT(result, 0);
}

TEST(test_assert_ne_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_ne(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_ne_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_ne(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_ne_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_ne(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_string_eq_pass, 0, 0)
{
  char a[] = "hello";
  char b[] = "hello";
  mute_stdout();
  int result = test_string_eq(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_string_eq_fail, 0, 0)
{
  char a[] = "hello";
  char b[] = "goodbye";
  mute_stdout();
  int result = test_string_eq(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(test_assert_mem_eq_pass, 0, 0)
{
  unsigned char a[] = { 0xAA, 0x55, 0xA5, 0x5A, 0xDE, 0xAD, 0xBE, 0xEF };
  unsigned char b[] = { 0xAA, 0x55, 0xA5, 0x5A, 0xDE, 0xAD, 0xBE, 0xEF };
  mute_stdout();
  int result = test_mem_eq(a, b, sizeof(a));
  unmute_stdout();

  TEST_EQ(result, 0);
}

TEST(test_assert_mem_eq_fail, 0, 0)
{
  unsigned char a[] = { 0xAA, 0x55, 0xA5, 0x5A, 0xDE, 0xAD, 0xBE, 0xEF };
  unsigned char b[] = { 0xAA, 0x55, 0xA5, 0x5A, 0xBE, 0xEF, 0xBA, 0xBE };
  mute_stdout();
  int result = test_mem_eq(a, b, sizeof(a));
  unmute_stdout();

  TEST_EQ(result, 1);
}

TEST(print_dashed_name_to_string_odd_name_even_len, 0, 0)
{
  char s[120];

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 14);
  TEST_STRING_EQ(s, "---- hello ---");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 12);
  TEST_STRING_EQ(s, "--- hello --");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 10);
  TEST_STRING_EQ(s, "-- hello -");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 8);
  TEST_STRING_EQ(s, "- hello ");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 6);
  TEST_STRING_EQ(s, " hello");
}

TEST(print_dashed_name_to_string_odd_name_odd_len, 0, 0)
{
  char s[120];

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 15);
  TEST_STRING_EQ(s, "---- hello ----");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 13);
  TEST_STRING_EQ(s, "--- hello ---");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 11);
  TEST_STRING_EQ(s, "-- hello --");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 9);
  TEST_STRING_EQ(s, "- hello -");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 7);
  TEST_STRING_EQ(s, " hello ");

  print_dashed_name_to_string(s, "hello", sizeof("hello") - 1, 5);
  TEST_STRING_EQ(s, "hello");
}

TEST(print_dashed_name_to_string_even_name_even_len, 0, 0)
{
  char s[120];

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 14);
  TEST_STRING_EQ(s, "--- banana ---");

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 12);
  TEST_STRING_EQ(s, "-- banana --");

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 10);
  TEST_STRING_EQ(s, "- banana -");

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 8);
  TEST_STRING_EQ(s, " banana ");

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 6);
  TEST_STRING_EQ(s, "banana");
}

TEST(print_dashed_name_to_string_even_name_odd_len, 0, 0)
{
  char s[120];

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 15);
  TEST_STRING_EQ(s, "--- banana ----");

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 13);
  TEST_STRING_EQ(s, "-- banana ---");

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 11);
  TEST_STRING_EQ(s, "- banana --");

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 9);
  TEST_STRING_EQ(s, " banana -");

  print_dashed_name_to_string(s, "banana", sizeof("banana") - 1, 7);
  TEST_STRING_EQ(s, "banana ");
}

TEST(can_use_percent_in_test_assert, 0, 0)
{
  /* To test that we can use a percent in a test assert, we pass it as a
   * parameter to a test assert. If this compiles successfully, then there is
   * no trouble with the implementation of the test macro placing stringified
   * parameters into format strings. */
  TEST_EQ(0, 8 % 4);
}
