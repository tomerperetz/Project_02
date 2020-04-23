#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include "errorHandler.h"
#include "linkedList.h"
#include "parser.h"

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

void printOutput(node *head, const command *usr_cmd)
{
	node *curr_node = head;
	//bool print_count_only = usr_cmd->enabled.print_count_only;

	while (curr_node != NULL)
	{
		if (curr_node->match)
			printf("%s\n", curr_node->line);

		curr_node = curr_node->next;
	}
}

void searchNeedle(node *head, const command *usr_cmd)
{
	node *curr_node = head;
	bool match_case = usr_cmd->enabled.match_case;
	bool wrap_around = usr_cmd->enabled.wrap_around;
	bool invert_match = usr_cmd->enabled.invert_match;
	bool res = false;
	char *needle = (char*)malloc((strlen(usr_cmd->search_str)+1)*sizeof(char));
	char *haist = NULL;
	
	strcpy(needle, usr_cmd->search_str);

	while (curr_node != NULL)
	{
		haist = (char*)malloc((strlen(curr_node->line)+1) * sizeof(char));
		strcpy(haist, curr_node->line);

		if (!match_case)
			lowerCase(haist);

		if (wrap_around)
		{ 
			if (strstr(haist, needle) != NULL)
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
		free(haist);
		haist = NULL;
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
