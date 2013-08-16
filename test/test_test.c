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
#include <unistd.h>
#include <fcntl.h>

#if _WIN32
#define NULL_FILE "NUL"
#else
#define NULL_FILE "/dev/null"
#endif

/* This comes from test/test.c. */
extern void print_dashed_name_to_string(
  char *s, const char *name, const size_t name_len, const size_t line_len
);

static int old_stdout = -1;
static int null_file = -1;
static void mute_stdout(void)
{
  fflush(stdout);
  old_stdout = dup(1);
  null_file = open(NULL_FILE, O_WRONLY);
  dup2(null_file, 1);
}

static void unmute_stdout(void)
{
  fflush(stdout);
  close(null_file);
  dup2(old_stdout, 1);
}

static int test_true(int condition)
{
  TEST_TRUE(condition);
  return 0;
}

static int test_false(int condition)
{
  TEST_FALSE(condition);
  return 0;
}

static int test_gt(int a, int b)
{
  TEST_GT(a, b);
  return 0;
}

static int test_lt(int a, int b)
{
  TEST_LT(a, b);
  return 0;
}

static int test_ge(int a, int b)
{
  TEST_GE(a, b);
  return 0;
}

static int test_le(int a, int b)
{
  TEST_LE(a, b);
  return 0;
}

static int test_eq(int a, int b)
{
  TEST_EQ(a, b);
  return 0;
}

static int test_ne(int a, int b)
{
  TEST_NE(a, b);
  return 0;
}

TEST(test_assert_true_pass, 0, 0)
{
  int a = 1;
  /* While testing the test, disable stdout. */
  mute_stdout();
  int result = test_true(a);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_true_fail, 0, 0)
{
  int a = 0;
  mute_stdout();
  int result = test_true(a);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_false_pass, 0, 0)
{
  int a = 0;
  mute_stdout();
  int result = test_false(a);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_false_fail, 0, 0)
{
  int a = 1;
  mute_stdout();
  int result = test_false(a);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_gt_gt_with_lt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_gt(a, b);
  unmute_stdout();

  TEST_LT(result, 1);

  return 0;
}

TEST(test_assert_gt_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_gt(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_gt_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_gt(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_gt_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_gt(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_lt_lt_with_true, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_TRUE(result == 0);

  return 0;
}

TEST(test_assert_lt_eq_with_true, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_TRUE(result == 1);

  return 0;
}

TEST(test_assert_lt_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_lt_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_lt_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_lt(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_ge_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_ge(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_ge_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_ge(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_ge_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_ge(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_le_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_le(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_le_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_le(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_le_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_le(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_eq_gt_with_ne, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_eq(a, b);
  unmute_stdout();

  TEST_NE(result, 0);

  return 0;
}

TEST(test_assert_eq_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_eq(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_eq_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_eq(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
}

TEST(test_assert_eq_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_eq(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_ne_eq_with_gt, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_ne(a, b);
  unmute_stdout();

  TEST_GT(result, 0);

  return 0;
}

TEST(test_assert_ne_gt, 0, 0)
{
  int a = 1;
  int b = 0;
  mute_stdout();
  int result = test_ne(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_ne_lt, 0, 0)
{
  int a = 0;
  int b = 1;
  mute_stdout();
  int result = test_ne(a, b);
  unmute_stdout();

  TEST_EQ(result, 0);

  return 0;
}

TEST(test_assert_ne_eq, 0, 0)
{
  int a = 0;
  int b = 0;
  mute_stdout();
  int result = test_ne(a, b);
  unmute_stdout();

  TEST_EQ(result, 1);

  return 0;
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

  return 0;
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

  return 0;
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

  return 0;
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

  return 0;
}
