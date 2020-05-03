/*
====================================================================================================================
Description:
this lib is used for parsering functions.
====================================================================================================================
*/

// Includes ------------------------------------------------------------------------------->
#define _CRT_SECURE_NO_WARNINGS
#include "errorHandler.h"
#include "parser.h"

// Private Functions ---------------------------------------------------------------------->


int getRegexLen(regex_char **regex_char_arr)
{
	int i = 0;
	while (regex_char_arr[i] != NULL) i++;
	return i;
}
void print_regex(regex_char **regex_char_arr)
{
	int i;
	char start;
	char end;
	int size = getRegexLen(regex_char_arr);
	for (i = 0; i < size; i++)
	{
		if (regex_char_arr[i] == NULL)
		{
			break;
		}
		if (regex_char_arr[i]->regex_char_type == SIMPLE_CHAR)
			printf("%c", regex_char_arr[i]->data.simple_char);

		if (regex_char_arr[i]->regex_char_type == DOT)
			printf("\ndot operator\n");

		if (regex_char_arr[i]->regex_char_type == SQUARE_BRACKET)
		{
			start = regex_char_arr[i]->data.square_brackets.start;
			end = regex_char_arr[i]->data.square_brackets.end;
			printf("\n");
			printf("start: %c, end: %c\n", start, end);
			for (char c = start; c<end; c++)
				printf("%c ", c);
			printf("\n");
		}

		if (regex_char_arr[i]->regex_char_type == ROUND_BRACKET)
		{
			printf("\n");
			printf("first option: %s\n", regex_char_arr[i]->data.round_brackets.str1);
			printf("second option: %s\n", regex_char_arr[i]->data.round_brackets.str2);
		}
		
	}
	printf("\n");
}

void copyCharByChar(char* src, char* dst, int start, int size)
{
	int i = 0;
	for (i; i < size; i++)
	{
		dst[i] = src[i + start];
	}
	dst[i] = '\0';
}

int getRegStrSize(char *str, char delimiter, int start_idx, int max_size)
{
	int i = start_idx;
	int size = 0;

	for (i = start_idx; str[i] != delimiter; i++)
	{
		if (i >= max_size) return ERR;
		size++;
	}
	return size;
}

int parseRoundBreckets(char* str_in, int curr_idx, int size, regex_char *regex_char)
{
	int i = 0;
	int first_start_idx = curr_idx+1;
	int first_size = 0;
	int second_start_idx = 0;
	int second_size = 0;
	int close_bracket = curr_idx; 

	first_size = getRegStrSize(str_in, '|', first_start_idx, size);
	second_start_idx = first_start_idx + first_size + 1;
	second_size = getRegStrSize(str_in, ')', second_start_idx, size);

	if (first_size == ERR || second_size == ERR)
	{
		raiseError(ERR_ILLEGAL_STRING_ID, __FILE__, __func__, __LINE__, ERR_ILLEGAL_STRING__CONTENT);
		return ERR;
	}

	close_bracket = second_start_idx + second_size;
	regex_char->data.round_brackets.str1 = (char*)malloc(sizeof(char)*(first_size+1));
	regex_char->data.round_brackets.str2 = (char*)malloc(sizeof(char)*(second_size+1));
	copyCharByChar(str_in, regex_char->data.round_brackets.str1, first_start_idx, first_size);
	copyCharByChar(str_in, regex_char->data.round_brackets.str2, second_start_idx, second_size);

	return close_bracket;
}

int parseSquareBreckets(char* str_in, int curr_idx, int size, regex_char *regex_char)
{
	int open_bracket = curr_idx;
	int start_idx = curr_idx + 1;
	int delimiter = curr_idx + 2;
	int end_idx = curr_idx + 3;
	int close_bracket = curr_idx + 4;
	bool valid = true;

	// check input is valid
	if (close_bracket > size)
		valid = false;
	else if ((str_in[close_bracket] != ']') || (str_in[delimiter] != '-'))
		valid = false;
	else
	{
		regex_char->regex_char_type = SQUARE_BRACKET;
		regex_char->data.square_brackets.start = str_in[start_idx];
		regex_char->data.square_brackets.end = str_in[end_idx];
	}

	if (valid)
		return close_bracket;
	else
	{
		raiseError(ERR_ILLEGAL_STRING_ID, __FILE__, __func__, __LINE__, ERR_ILLEGAL_STRING__CONTENT);
		return ERR;
	}
}

void upperToLowerCase(char *action_string) {
	size_t idx = 0;

	for (idx = 0; idx < strlen(action_string); idx++) {
		action_string[idx] = tolower(action_string[idx]);
	}
}

void checkGrepOption(char *argument, command* input_command, int *A_flag) {
	switch (argument[1]) {
	case 'A':
		input_command->enabled.print_extra_lines = true;
		if (argument[2] != '\0') {
			input_command->enabled.num_of_extra_lines = atoi(argument + 2);
		}
		else {
			*A_flag = true;
		}
		break;
	case 'b':
		input_command->enabled.print_bytes = true;
		break;
	case 'c':
		input_command->enabled.print_count_only = true;
		break;
	case 'E':
		input_command->enabled.extended_regexp = true;
		break;
	case 'i':
		input_command->enabled.match_case = false;
		break;
	case 'n':
		input_command->enabled.print_line_number = true;
		break;
	case 'v':
		input_command->enabled.invert_match = true;
		break;
	case 'x':
		input_command->enabled.wrap_around = false;
		break;
	}

}

char* insertStrToCommand(char *destination_str, const char *argument, bool regular_expression) {
	size_t str_size = 0;
	bool back_slash_flag = false, in_string = true;
	int dest_idx = 0, arg_idx = 0;

	str_size = strlen(argument) + 1;
	destination_str = (char*)malloc(sizeof(char)*str_size);
	if (destination_str == NULL) {
		raiseError(ERR_MEM_ALLOC_ID, __FILE__, __func__, __LINE__, ERR_MEM_ALLOC_CONTENT);
		return NULL;
	}

	while (in_string) {
		if (regular_expression) {
			if (back_slash_flag) {
				destination_str[dest_idx] = argument[arg_idx];
				back_slash_flag = false;
				arg_idx++;
				dest_idx++;
				continue;
			}
			if (argument[arg_idx] == '\\') {
				back_slash_flag = true;
				arg_idx++;
				continue;
			}
		}
		destination_str[dest_idx] = argument[arg_idx];
		if (destination_str[dest_idx] == '\n') {
			destination_str[dest_idx] = '\0';
		}
		if (destination_str[dest_idx] == '\0') in_string = false;
		arg_idx++;
		dest_idx++;
	}
	return destination_str;

}

// Public Functions ---------------------------------------------------------------------->
void freeRegex(regex_char **regex_char_arr)
{
	int i = 0;
	int size = getRegexLen(regex_char_arr);
	for (i = 0; i < size; i++)
	{
		if (regex_char_arr[i] == NULL)
			break;
		if (regex_char_arr[i]->regex_char_type == ROUND_BRACKET)
		{
			free(regex_char_arr[i]->data.round_brackets.str1);
			free(regex_char_arr[i]->data.round_brackets.str2);
		}
		free(regex_char_arr[i]);
	}

	free(regex_char_arr);
}

regex_char** regexParser(char* str_in)
{
	int i = 0;
	int j = 0;
	size_t size = strlen(str_in);

	// allocate memory for regex
	regex_char **regex_char_arr = (regex_char**)malloc(sizeof(regex_char*)*(size+1));

	for (i = 0; i < (int)size; i++)
	{
		regex_char_arr[i] = (regex_char*)malloc(sizeof(regex_char));
	}

	// parse str in
	for (i = 0, j=0; i < size; i++, j++)
	{
		switch (str_in[i])
		{
			case ('\\'):
			{
				regex_char_arr[j]->data.simple_char = str_in[i + 1];
				regex_char_arr[j]->regex_char_type = SIMPLE_CHAR;
				i++;
				break;
			}

			case ('.'):
			{
				regex_char_arr[j]->data.dot = true;
				regex_char_arr[j]->regex_char_type = DOT;
				break;
			}

			case ('['):
			{
				regex_char_arr[j]->regex_char_type = SQUARE_BRACKET;
				i = parseSquareBreckets(str_in, i, size, regex_char_arr[j]);
				if (i == ERR)
					return NULL;
				break;
			}

			case ('('):
			{
				regex_char_arr[j]->regex_char_type = ROUND_BRACKET;
				i = parseRoundBreckets(str_in, i, size, regex_char_arr[j]);
				if (i == ERR)
					return NULL;
				break;
			}

			default:
			{
				regex_char_arr[j]->data.simple_char = str_in[i];
				regex_char_arr[j]->regex_char_type = SIMPLE_CHAR;
				break;
			}
		}
	}
	regex_char_arr[j] = NULL;
	return regex_char_arr;
}

void test_regex_parser()
{
	int i = 0;
	size_t str_len = 0;
	char* str_test[100];
	int ret_val = true;
	regex_char **regex_char_arr = NULL;
	scanf("%s", &str_test);
	str_len = strlen(str_test) + 1;
	regex_char_arr = regexParser(str_test);
	if (regex_char_arr == NULL) goto free_mem;
	print_regex(regex_char_arr);

free_mem:
	freeRegex(regex_char_arr);
}

void initializeCommand(command *input_command) {
	input_command->search_str = NULL;
	input_command->file_path = NULL;
	input_command->enabled.print_extra_lines = false;
	input_command->enabled.num_of_extra_lines = false;
	input_command->enabled.print_bytes = false;
	input_command->enabled.print_count_only = false;
	input_command->enabled.extended_regexp = false;
	input_command->enabled.match_case = true;
	input_command->enabled.print_line_number = false;
	input_command->enabled.invert_match = false;
	input_command->enabled.wrap_around = true;
	input_command->std_in = false;

}

void printCommand(command input_command) {
	if (input_command.search_str == NULL) {
		printf("Search string is:            NULL\n");
	}
	else {
		printf("Search string is:            %s\n", input_command.search_str);
	}
	if (input_command.std_in == false) {
		printf("File path is:                %s\n", input_command.file_path);
	}
	printf("Grep option print_extra_lines:%d   with num: %d\n", input_command.enabled.print_extra_lines,
 input_command.enabled.num_of_extra_lines);
	printf("Grep option print_bytes:                %d\n", input_command.enabled.print_bytes);
	printf("Grep option print_count_only:           %d\n", input_command.enabled.print_count_only);
	printf("Grep option extended_regexp:            %d\n", input_command.enabled.extended_regexp);
	printf("Grep option match_case:					%d\n", input_command.enabled.match_case);
	printf("Grep option print_line_number:          %d\n", input_command.enabled.print_line_number);
	printf("Grep option invert_match:               %d\n", input_command.enabled.invert_match);
	printf("Grep option wrap_around:                %d\n", input_command.enabled.wrap_around);
	printf("Input through stdin:					%d\n", input_command.std_in);
}

int commandParser(char **arguments_list, int arguments_amount, command *usr_cmd) {
	int idx = 2, A_flag = false, search_str_flag = false, file_path_flag = false;


	for (idx = 1; idx < arguments_amount; idx++) {
		if (A_flag == true) {
			usr_cmd->enabled.num_of_extra_lines = atoi(arguments_list[idx]);
			A_flag = false;
			continue;
		}
		if (arguments_list[idx][0] == '-') {
			checkGrepOption(arguments_list[idx], usr_cmd, &A_flag);
		}
		else {
			if (search_str_flag == false) {
				usr_cmd->search_str = insertStrToCommand(usr_cmd->search_str, arguments_list[idx], usr_cmd->enabled.extended_regexp);
				if (usr_cmd->search_str == NULL) {
					return false;
				}
				search_str_flag = true;
				continue;
			}
			else {
				usr_cmd->file_path = insertStrToCommand(usr_cmd->file_path, arguments_list[idx], usr_cmd->enabled.extended_regexp);
				if (usr_cmd->file_path == NULL) {
					return false;
				}
				file_path_flag = true;
				break;
			}
		}
	}
	if (file_path_flag == false) {          // check if there is a better way to do it. 
		usr_cmd->std_in = true;
	}
	return true;
}

void freeCommand(command *input_command) {
	if (input_command->search_str != NULL) {
		free((input_command->search_str));
	}
	if (input_command->file_path != NULL) {
		free(input_command->file_path);
	}
}

