#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include "errorHandler.h"
#include "linkedList.h"
#include "parser.h"
#define END -1
#define STRCMP_TRUE 1
#define STRCMP_SUBSTRING 2

void lowerCase(char *str)
{
	int i = 0;
	/*
	Description: recieve char array in any form (lower/higher/mixed case) and convert all to lower case
	parameters:
			 - char *str
	Returns: void, convert arr itself
	*/
	for (i = 0; str[i] != '\0'; i++)
		str[i] = tolower(str[i]);
}

int rowCount(node *head) {
	node *curr_node = head;
	int counter = 0;

	while (curr_node != NULL)
	{
		if (curr_node->match)
			counter++;
		curr_node = curr_node->next;
	}
	return counter;
}

void printNode(node *curr_node, const command *usr_cmd, const char sign) {
		
	if (usr_cmd->enabled.print_line_number) {
		printf("%d%c", curr_node->line_number, sign);
	}
	if (usr_cmd->enabled.print_bytes) {
		printf("%d%c", curr_node->byte_number, sign);
	}
	printf("%s\n", curr_node->line);
}

int printANode(node *curr_node, const command *usr_cmd , int rows_left_to_print, bool *separator_enable) {
	int rows = rows_left_to_print;

	if (curr_node->match) {
		if (*separator_enable) {
			printf("--\n");
			*separator_enable = false;
		}
		rows = usr_cmd->enabled.num_of_extra_lines;
		printNode(curr_node, usr_cmd, ':');
		if (curr_node->next == NULL) return END;
	}
	else {
		if (rows != 0) {
			printNode(curr_node, usr_cmd, '-');
			rows--;
			if (curr_node->next == NULL) return END;
			if (rows == 0 && !curr_node->next->match) {
				*separator_enable = true;
			}
				
		}
	}
	return rows;
}

void printOutput(node *head, const command *usr_cmd)
{
	node *curr_node = head;
	int rows_left_to_print = 0;
	bool print_count_only = usr_cmd->enabled.print_count_only, separator_enable = false ;

	if (print_count_only) {
		printf("%d\n", rowCount(curr_node));
		return;
	}

	while (curr_node != NULL)
	{
		if (usr_cmd->enabled.print_extra_lines) {
			rows_left_to_print = printANode(curr_node, usr_cmd, rows_left_to_print, &separator_enable);
		}
		else if (curr_node->match){
				printNode(curr_node, usr_cmd, ':');
		}
		curr_node = curr_node->next;
	}
}

bool compareRegexChars(const char haystack, regex_char *needle, int *stack_step_size)
{
	bool condition = false;
	//bool a_string = false;
	//bool b_string = false;
	char min = 0;
	char max = 0;
	//regex_char** sub_needle_1 = NULL;
	//regex_char** sub_needle_2 = NULL;

	switch (needle->regex_char_type)
	{
	case SIMPLE_CHAR:
	{
		condition = (needle->data.simple_char == haystack);
		break;
	}
	case DOT:
	{
		condition = true;
		break;
	}
	case SQUARE_BRACKET:
	{
		min = needle->data.square_brackets.start;
		max = needle->data.square_brackets.end;
		condition = (haystack >= min && haystack <= max);
		break;
	}
	case ROUND_BRACKET:
	{	
		printf("we are not doing this yet\n");
		*stack_step_size = 0;  //just to deel with unused parameter warning
		/*sub_needle_1 = regexParser(needle->data.round_brackets.str1);
		sub_needle_2 = regexParser(needle->data.round_brackets.str2);

		a_string = MyStrCmp(haystack, sub_needle_1);
		if (a_string)
			*stack_step_size = strlen(needle->data.round_brackets.str1);
		b_string = MyStrCmp(haystack, sub_needle_2);
		if (b_string)
			*stack_step_size = strlen(needle->data.round_brackets.str2);

		if (a_string || b_string) condition = true;

		freeRegex(sub_needle_1);
		freeRegex(sub_needle_2);*/
	}
	}
	return condition;
}

int MyStrCmp(const char *haystack, regex_char **needle)
{
	bool condition = false;
	int i;
	int stack_step_size = 1;
	size_t haystack_size = strlen(haystack);

	if (haystack_size == 0)
		return STRCMP_SUBSTRING;;

	for (i = 0; i < (int)haystack_size; i++)
	{
		if (needle[i] == 0)
			break;
		condition = compareRegexChars(haystack[i], needle[i], &stack_step_size);
		if (!condition)
			return false;

		if (stack_step_size > 1) i = i + stack_step_size;
	}

	if (i == (int)haystack_size)
		return STRCMP_TRUE;
	else
		return STRCMP_SUBSTRING;
}

char *RecStrStr(const char *haystack, regex_char **needle)
{
	bool condition = false;
	int stack_step_size = 1;
	if (*needle == 0)
		return (char*)haystack;

    if(*haystack == 0)
        return NULL;
	
	condition = compareRegexChars(haystack[0], needle[0], &stack_step_size);

	if(condition && RecStrStr(haystack + stack_step_size, needle + 1) == haystack + stack_step_size)
        return (char *)haystack;

    return RecStrStr(haystack + 1, needle);
}

void searchNeedle(node *head, const command *usr_cmd)
{
	node *curr_node = head;
	//bool print_count_only = usr_cmd->enabled.print_count_only;
	bool match_case = usr_cmd->enabled.match_case;
	bool wrap_around = usr_cmd->enabled.wrap_around;
	bool invert_match = usr_cmd->enabled.invert_match;
	bool res = false;
	char *needle = (char*)malloc((strlen(usr_cmd->search_str)+1)*sizeof(char));
	char *haystack = NULL;
	regex_char** needle_regex = NULL;
	strcpy(needle, usr_cmd->search_str);

	while (curr_node != NULL)
	{
		haystack = (char*)malloc((strlen(curr_node->line)+1) * sizeof(char));
		strcpy(haystack, curr_node->line);

		if (!match_case) {
			lowerCase(haystack);
			lowerCase(needle);
		}
		needle_regex = regexParser(needle);

		if (wrap_around)
		{ 
			if (RecStrStr(haystack, needle_regex) != NULL)
				res = true;
			else
				res = false;
		}
		else {

			if (MyStrCmp(haystack, needle_regex) == STRCMP_TRUE)
				res = true;
			else
				res = false;
		}

		if (invert_match)
		{
			res = !res;
		}
		curr_node->match = res;
		curr_node = curr_node->next;
		free(haystack);
		haystack = NULL;
	}

	free(needle);
}

void my_grep(const command *usr_cmd, node *head)
{
	if(head == NULL) return;
	searchNeedle(head, usr_cmd);
	printOutput(head, usr_cmd);
}

int main(int argc, char *argv[])
{
	node *head = NULL;
	char *line_buffer = NULL;
	size_t line_buffer_size = 0;
	size_t line_size;
	int line_count = 0;
	command usr_cmd;
	FILE *fp = NULL;
	int ret_val = EXIT_SUCCESS;

	initializeCommand(&usr_cmd);
	commandParser(argv, argc, &usr_cmd);

	if (usr_cmd.std_in)
		fp = stdin;
	else
	{
		fp = fopen(usr_cmd.file_path, "r");
		if (!fp)
		{
			fprintf(stderr, "Error opening file '%s'\n", usr_cmd.file_path);
			raiseError(ERR_IO_ID, __FILE__, __func__, __LINE__, ERR_IO_CONTENT);
			ret_val =  EXIT_FAILURE;
			goto free_mem_and_exit;
		}
	}

	line_size = getline(&line_buffer, &line_buffer_size, fp);
	while ((int)line_size != EOF)
	{

		line_count++; // line counter starts from 1 - like real grep
		head = insertEnd(head, line_buffer, line_count, line_size);
		free(line_buffer);
		line_buffer = NULL;
		line_size = getline(&line_buffer, &line_buffer_size, fp);
	}
	
	free(line_buffer);
	fclose(fp);
	my_grep(&usr_cmd, head);
	freeList(head);
	goto free_mem_and_exit;

free_mem_and_exit:
	freeCommand(&usr_cmd);
	return ret_val;
}


//int main()
//{
//	while (1) test_regex_parser();
//}