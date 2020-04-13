#ifndef PARSER_H
#define PARSER_H
// Includes Stractures --------------------------------------------------------------------->

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


// Defines ---------------------------------------------------------------------->
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

// Public Stractures --------------------------------------------------------------------->

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
	grep_options enabled;
	char* file_path;
} command;

// Public Functions ---------------------------------------------------------------------->



#endif
