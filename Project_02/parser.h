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

#define SIMPLE_CHAR 1
#define DOT 2
#define SQUARE_BRACKET 3
#define ROUND_BRACKET 4


typedef struct _grep_options
{
	bool print_extra_lines;
	int num_of_extra_lines;
	bool print_bytes;
	bool print_count_only;
	bool match_case;
	bool print_line_number;
	bool invert_match;
	bool wrap_around;
	bool extended_regexp;

} grep_options;

typedef struct _command
{
	char* search_str;
	char* file_path;
	grep_options enabled;
	bool std_in;
} command;

typedef struct _square_brackets
{
	char start;
	char end;

} square_brackets;

typedef struct _round_brackets
{
	char* str1;
	char* str2;
} round_brackets;

typedef union _regex_char_data
{
	char simple_char;
	bool dot;
	square_brackets square_brackets;
	round_brackets round_brackets;
} regex_char_data;

typedef struct _regex_char
{
	union _regex_char_data data;
	int regex_char_type;
} regex_char;

void test_regex_parser();

void initializeCommand(command *input_command);

void printCommand(command input_command);

int commandParser(char **arguments_list, int arguments_amount, command *input_command);

void freeCommand(command *input_command);


#endif
