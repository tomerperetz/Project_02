.PHONY: all clean test

all: my_grep 

clean:
	-rm *.o my_grep

test: my_grep
	./run_test.sh

my_grep: my_grep.o errorHandler.o linkedList.o parser.o
	gcc -o my_grep my_grep.o errorHandler.o linkedList.o parser.o 

my_grep.o: my_grep.c errorHandler.h parser.h
	gcc -c -Wall -Wextra my_grep.c
	
errorHandler.o: errorHandler.c errorHandler.h
	gcc -c -Wall -Wextra errorHandler.c

linkedList.o: linkedList.c linkedList.h errorHandler.h
	gcc -c -Wall -Wextra linkedList.c

parser.o: parser.c parser.h errorHandler.h
	gcc -c -Wall -Wextra parser.c


	