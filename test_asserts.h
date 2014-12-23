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
  if (!silent) \
  { \
    printf("%s", failure_message_buffer); \
  } \
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
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s'" \
        " (expected true, was false)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, \
        #condition \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '%s'" \
        " (expected true, was false)\n", \
        __LINE__, \
        #condition \
      ); \
    } \
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
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s'" \
        " (expected false, was true)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, \
        #condition \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '%s'" \
        " (expected false, was true)\n", \
        __LINE__, \
        #condition \
      ); \
    } \
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
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s > %s'" \
        " (%s=%td, %s=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '%s > %s'" \
        " (%s=%td, %s=%td)\n", \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
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
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s < %s'" \
        " (%s=%td, %s=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '%s < %s'" \
        " (%s=%td, %s=%td)\n", \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
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
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s >= %s'" \
        " (%s=%td, %s=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '%s >= %s'" \
        " (%s=%td, %s=%td)\n", \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
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
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s <= %s'" \
        " (%s=%td, %s=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '%s <= %s'" \
        " (%s=%td, %s=%td)\n", \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
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
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s == %s'" \
        " (%s=%td, %s=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '%s == %s'" \
        " (%s=%td, %s=%td)\n", \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
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
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s != %s'" \
        " (%s=%td, %s=%td)\x1b[0m\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
    else \
    { \
      snprintf( \
        failure_message_buffer, \
        sizeof(failure_message_buffer), \
        __FILE__ ":%d\x1b[K\nTest failed: '%s != %s'" \
        " (%s=%td, %s=%td)\n", \
        __LINE__, \
        #a, #b, \
        #a, (ptrdiff_t)(a), \
        #b, (ptrdiff_t)(b) \
      ); \
    } \
    TEST_FAIL(); \
  } \
} while(0)

#define TEST_STRING_EQ(a, b) \
do { \
  if (strcmp(a, b)) \
  { \
    snprintf( \
      failure_message_buffer, \
      sizeof(failure_message_buffer), \
      "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\nTest failed: '%s != %s'" \
      " (%s=%s, %s=%s)\x1b[0m\n", \
      FOREGROUND_WHITE, BACKGROUND_RED, \
      __LINE__, \
      #a, #b, \
      #a, a, \
      #b, b \
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
      int written = 0; \
      size_t buffer_pos = 0; \
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
      written = snprintf( \
        &failure_message_buffer[buffer_pos], \
        sizeof(failure_message_buffer) - buffer_pos, \
        "\r\x1b[1;%d;%dm" __FILE__ ":%d\x1b[K\n" \
        "Test failed: '%s != %s'\n", \
        FOREGROUND_WHITE, BACKGROUND_RED, \
        __LINE__, #a, #b \
      ); \
      if (written > 0) buffer_pos += written; \
      /* Display buffer a */ \
      if (partial_start) \
      { \
        written = snprintf( \
          &failure_message_buffer[buffer_pos], \
          sizeof(failure_message_buffer) - buffer_pos, \
          "... " \
        ); \
        if (written > 0) buffer_pos += written; \
      } \
      for (size_t j = start; j < end; j++) \
      { \
        written = snprintf( \
          &failure_message_buffer[buffer_pos], \
          sizeof(failure_message_buffer) - buffer_pos, \
          "%02X ", a8[j] \
        ); \
        if (written > 0) buffer_pos += written; \
      } \
      if (partial_end) \
      { \
        written = snprintf( \
          &failure_message_buffer[buffer_pos], \
          sizeof(failure_message_buffer) - buffer_pos, \
          "... " \
        ); \
        if (written > 0) buffer_pos += written; \
      } \
      written = snprintf( \
        &failure_message_buffer[buffer_pos], \
        sizeof(failure_message_buffer) - buffer_pos, \
        ": " #a "\n" \
      ); \
      if (written > 0) buffer_pos += written; \
      /* Display buffer b */ \
      if (partial_start) \
      { \
        written = snprintf( \
          &failure_message_buffer[buffer_pos], \
          sizeof(failure_message_buffer) - buffer_pos, \
          "... " \
        ); \
        if (written > 0) buffer_pos += written; \
      } \
      for (size_t j = start; j < end; j++) \
      { \
        written = snprintf( \
          &failure_message_buffer[buffer_pos], \
          sizeof(failure_message_buffer) - buffer_pos, \
          "%02X ", b8[j] \
        ); \
        if (written > 0) buffer_pos += written; \
      } \
      if (partial_end) \
      { \
        written = snprintf( \
          &failure_message_buffer[buffer_pos], \
          sizeof(failure_message_buffer) - buffer_pos, \
          "... " \
        ); \
        if (written > 0) buffer_pos += written; \
      } \
      written = snprintf( \
        &failure_message_buffer[buffer_pos], \
        sizeof(failure_message_buffer) - buffer_pos, \
        ": " #b "\n" \
      ); \
      if (written > 0) buffer_pos += written; \
      /* Display error marker */ \
      if (partial_start) \
      { \
        written = snprintf( \
          &failure_message_buffer[buffer_pos], \
          sizeof(failure_message_buffer) - buffer_pos, \
          "    " \
        ); \
        if (written > 0) buffer_pos += written; \
      } \
      for (size_t j = start; j < end; j++) \
      { \
        if (j == i) \
        { \
          written = snprintf( \
            &failure_message_buffer[buffer_pos], \
            sizeof(failure_message_buffer) - buffer_pos, \
            "~~" \
          ); \
          if (written > 0) buffer_pos += written; \
          break; \
        } \
        else \
        { \
          written = snprintf( \
            &failure_message_buffer[buffer_pos], \
            sizeof(failure_message_buffer) - buffer_pos, \
            "   " \
          ); \
          if (written > 0) buffer_pos += written; \
        } \
      } \
      written = snprintf( \
        &failure_message_buffer[buffer_pos], \
        sizeof(failure_message_buffer) - buffer_pos, \
        "\x1b[0m\n" \
      ); \
      if (written > 0) buffer_pos += written; \
      TEST_FAIL(); \
      break; \
    } \
  } \
} while(0)

#endif
