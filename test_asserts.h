/*
 * This Source Code Form is subject to the terms of the Mozilla Public License,
 * v. 2.0. If a copy of the MPL was not distributed with this file, You can
 * obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2013 KIWI.KI GmbH.
 */

#include <string.h> // strcmp

#ifndef TEST_ASSERTS_H
#define TEST_ASSERTS_H

#include "test_colors.h"
#include <setjmp.h>

extern jmp_buf test_runner_env;

#define TEST_FAIL() \
  longjmp(test_runner_env, 1)

#define TEST_TRUE(condition) \
do { \
  if (!(condition)) \
  { \
    if (with_color) \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #condition \
        "' (expected true, was false)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__ \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '" #condition \
        "' (expected true, was false)\n", \
        __LINE__ \
      ); \
    } \
    printf("%s", failure_message_buffer); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_FALSE(condition) \
do { \
  if (condition) \
  { \
    if (with_color) \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #condition \
        "' (expected false, was true)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__ \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '" #condition \
        "' (expected false, was true)\n", \
        __LINE__ \
      ); \
    } \
    printf("%s", failure_message_buffer); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_GT(a, b) \
do { \
  if (!((a) > (b))) \
  { \
    if (with_color) \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #a " > " #b \
        "' (" #a "=%td, " #b "=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '" #a " > " #b \
        "' (" #a "=%td, " #b "=%td)\n", \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    printf("%s", failure_message_buffer); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_LT(a, b) \
do { \
  if (!((a) < (b))) \
  { \
    if (with_color) \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #a " < " #b \
        "' (" #a "=%td, " #b "=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '" #a " < " #b \
        "' (" #a "=%td, " #b "=%td)\n", \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    printf("%s", failure_message_buffer); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_GE(a, b) \
do { \
  if (!((a) >= (b))) \
  { \
    if (with_color) \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #a " >= " #b \
        "' (" #a "=%td, " #b "=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '" #a " >= " #b \
        "' (" #a "=%td, " #b "=%td)\n", \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    printf("%s", failure_message_buffer); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_LE(a, b) \
do { \
  if (!((a) <= (b))) \
  { \
    if (with_color) \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #a " <= " #b \
        "' (" #a "=%td, " #b "=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '" #a " <= " #b \
        "' (" #a "=%td, " #b "=%td)\n", \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    printf("%s", failure_message_buffer); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_EQ(a, b) \
do { \
  if (!((a) == (b))) \
  { \
    if (with_color) \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #a " == " #b \
        "' (" #a "=%td, " #b "=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '" #a " == " #b \
        "' (" #a "=%td, " #b "=%td)\n", \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    printf("%s", failure_message_buffer); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_NE(a, b) \
do { \
  if (!((a) != (b))) \
  { \
    if (with_color) \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #a " != " #b \
        "' (" #a "=%td, " #b "=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '" #a " != " #b \
        "' (" #a "=%td, " #b "=%td)\n", \
        __LINE__, (ptrdiff_t)(a), (ptrdiff_t)(b) \
      ); \
    } \
    printf("%s", failure_message_buffer); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_STRING_EQ(a, b) \
do { \
  if (strcmp(a, b)) \
  { \
    printf( \
      "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '" #a " != " #b \
      "' (" #a "=%s, " #b "=%s)\x1b[0m\n", \
      FOREGROUND_WHITE, BACKGROUND_RED, \
      __LINE__, a, b \
    ); \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_MEM_EQ(a, b, n) \
do { \
  unsigned char *a8 = (unsigned char *)a; \
  unsigned char *b8 = (unsigned char *)b; \
  for (size_t i = 0; i < n; i++) \
  { \
    if (a8[i] != b8[i]) \
    { \
      /* Determine context to display. */ \
      bool partial_start = false; \
      bool partial_end = true; \
      size_t context_before = 4; \
      size_t context_after = 4; \
      size_t start = 0; \
      if (i > context_before) \
      { \
        start = i - context_before; \
        partial_start = true; \
      } \
      size_t end = i + context_after + 1; \
      if (end >= n) \
      { \
        end = n; \
        partial_end = false; \
      } \
      printf( \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\n" \
        "Test failed: '" #a " != " #b "'\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__ \
      ); \
      /* Display buffer a */ \
      if (partial_start) printf("... "); \
      for (size_t j = start; j < end; j++) \
      { \
        printf("%02X ", a8[j]); \
      } \
      if (partial_end) printf("... "); \
      printf(": " #a "\n"); \
      /* Display buffer b */ \
      if (partial_start) printf("... "); \
      for (size_t j = start; j < end; j++) \
      { \
        printf("%02X ", b8[j]); \
      } \
      if (partial_end) printf("... "); \
      printf(": " #b "\n"); \
      /* Display error marker */ \
      if (partial_start) printf("    "); \
      for (size_t j = start; j < end; j++) \
      { \
        if (j == i) \
        { \
          printf("~~"); \
          break; \
        } \
        else \
        { \
          printf("   "); \
        } \
      } \
      printf("\x1b[0m\n"); \
      break; \
    } \
  } \
} while(0)

#endif
