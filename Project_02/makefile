CFLAGS=-01 -g

.PHONY: all clean test

all: my_grep 

clean:
	rm -rf *.o my_grep

test:
	sh run_tomer_tests.sh

my_grep: errorHandler.o linkedList.o parser.o my_grep.o
	gcc -g my_grep.o errorHandler.o linkedList.o parser.o -o my_grep -O0

my_grep.o: my_grep.c errorHandler.h parser.h linkedList.h
	gcc -c -std=gnu99 -Wall -Wextra my_grep.c -g
	
errorHandler.o: errorHandler.c errorHandler.h
	gcc -c -std=gnu99 -Wall -Wextra errorHandler.c -g

linkedList.o: linkedList.c linkedList.h errorHandler.h
	gcc -c -std=gnu99 -Wall -Wextra linkedList.c -g

parser.o: parser.c parser.h errorHandler.h
	gcc -c -std=gnu99 -Wall -Wextra parser.c -g
	

