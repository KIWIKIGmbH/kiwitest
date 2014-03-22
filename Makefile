CFLAGS=-g -std=c99 -pedantic -Wall -Wextra -Werror

all: kiwitest

kiwitest: test_test.o test.o junit_xml.o

clean:
	rm -f *.o
	rm -f kiwitest
