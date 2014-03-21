kiwitest
========
kiwitest is a C unit testing toolbox. It's full of helpful macros to help you
create a program that will unit test your C code.

Requirements
------------
* ISO C99 Compiler
* Some C code to test

Optional Requirements
---------------------
* Make (to build the example test runner more easily)

Dependencies
------------
* None

Usage
=====
1. Build an executable with some tests in it. Make it return non-zero when your
   tests fail.
   * You can use the provided kiwitest.c as a starting point for making your
     own test runner.
   * To build the provided kiwitest.c, run "make" if make is available.
1. Set up your build system to run this executable. Fail your build if the test
   executable returns non-zero. Display results or use the XML file from
   Jenkins or something.
   * The provided test runner accepts some command line options.
     - The "-v" option will provide more verbose output.
     - The "-f junit_xml_output_filepath" option will output J Unit style XML
       to the specified file.
1. ...
1. Profit!

License
=======
MPL2 licensed. See LICENSE file.
