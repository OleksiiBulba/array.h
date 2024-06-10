CC=cc
CFLAGS=-Wall -Wextra

all: test_array

bin/test_array: test_array.o
	$(CC) $(CFLAGS) -o bin/test_array bin/test_array.o

bin/test_array.o: test_array.c array.h
	$(CC) $(CFLAGS) -g -c bin/test_array.c

clean:
	rm -f bin/*.o bin/test_array

run: test_array
	bin/test_array

memleaks:
	cc -fsanitize=address -o test test.c -Wall -Wextra -g && ./test

