#ifndef JUNIT_XML_H
#define JUNIT_XML_H

#include <stdio.h>

FILE *junit_xml_init(const char *path);

void junit_xml_finalize(FILE *junit_xml_file);

void junit_xml_begin_testsuites(FILE *junit_xml_file);

void junit_xml_end_testsuites(FILE *junit_xml_file);

void junit_xml_begin_testsuite(
  FILE *junit_xml_file, const char *testsuite_name, size_t num_tests
);

void junit_xml_end_testsuite(FILE *junit_xml_file);

void junit_xml_pass_testcase(
  FILE *junit_xml_file, const char *classname, const char *testcase_name,
  float time
);

void junit_xml_fail_testcase(
  FILE *junit_xml_file,
  const char *classname, const char *testcase_name, float time,
  const char *failure_message
);

#endif
