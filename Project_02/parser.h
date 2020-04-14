#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE_LEN 100
#define LONGEST_INT_SIZE 11
#define ADD_END 1
#define ADD_START 2
#define ADD_AFTER 3
#define INDEX 4
#define DEL 5
#define PRINT 6
#define EXIT 7
#define NO_ACTION 8
#define ASCI_NUMBER_FOR_0 48
#define ASCI_NUMBER_FOR_9 57
#define SEARCH_STR 1
#define FILE_PATH 2

typedef struct _grep_options
{
	bool A;
	int A_num;
	bool b;
	bool c;
	bool i;
	bool n;
	bool v;
	bool x;
	bool E;

} grep_options;

typedef struct _command
{
	char* search_str;
	char* file_path;
	grep_options enabled;
	bool std_in;
} command;


void initializeCommand(command *input_command);

void printCommand(command input_command);

int commandParser(char **arguments_list, int arguments_amount, command *input_command);

void freeCommand(command *input_command);


#endif
