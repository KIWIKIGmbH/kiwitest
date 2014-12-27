CFLAGS=-g -std=c99 -pedantic -Wall -Wextra -Werror \
       -DKIWITEST_TIME_MEASUREMENT=1 \
       -DKIWITEST_JUNIT_XML=1 \

all: kiwitest

kiwitest: test_test.o test.o junit_xml.o

clean:
	rm -f *.o
	rm -f kiwitest
