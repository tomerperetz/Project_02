#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include "errorHandler.h"
#include "linkedList.h"
#include "parser.h"

#define END -1

//void parseDestStr(const char *str)
//{
//	printf("Parsing User str");
//}


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
void searchNeedle(node *head, const command *usr_cmd)
{
	node *curr_node = head;
	bool print_count_only = usr_cmd->enabled.print_count_only;
	bool match_case = usr_cmd->enabled.match_case;
	bool wrap_around = usr_cmd->enabled.wrap_around;
	bool invert_match = usr_cmd->enabled.invert_match;
	bool res = false;
	char *needle = (char*)malloc((strlen(usr_cmd->search_str)+1)*sizeof(char));
	char *haystack = NULL;
	
	strcpy(needle, usr_cmd->search_str);

	while (curr_node != NULL)
	{
		haystack = (char*)malloc((strlen(curr_node->line)+1) * sizeof(char));
		strcpy(haystack, curr_node->line);

		if (!match_case) {
			lowerCase(haystack);
			lowerCase(needle);
		}

		if (wrap_around)
		{ 
			if (strstr(haystack, needle) != NULL)
				res = true;
			else
				res = false;
			
		}
		else {
			if (strcmp(haystack, needle) == 0)
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
