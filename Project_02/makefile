.PHONY: all clean test

all: my_grep 

clean:
	-rm *.o my_exec

test: my_exec
	./run_test.sh




my_grep: my_grep.o errorHandler.o linkedList.o parser.o
	gcc mygrep.o errorHandler.o linkedList.o parser.o -0 my_grep

my_grep.o: my_grep.c errorHandler.h

errorHandler.o: errorHandler.c errorHandler.h

linkedList.o: linkedList.c linkedList.h errorHandler.h

parser.o: parser.c parser.h errorHandler.h


	