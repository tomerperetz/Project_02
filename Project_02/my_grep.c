#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include "errorHandler.h"
#include "linkedList.h"
#include "parser.h"


void my_grep(const command *usr_cmd, const node *head)
{
}

bool isLineMatch(const char *heist, const char *needle)
{
	if (strstr(heist, needle) != NULL) return true;
	return false;
}

int main(int argc, char *argv[])
{
	node *head = NULL;
	char *line_buffer = NULL;
	size_t line_buffer_size = 0;
	size_t line_size;
	int line_count = 0;
	command usr_cmd;
	FILE *fp;
	bool is_str_in_line;

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
			return EXIT_FAILURE;
		}
	}
	line_size = getline(&line_buffer, &line_buffer_size, fp);
	
	while ((int)line_size != EOF)
	{
		line_count++;
		is_str_in_line = isLineMatch(line_buffer, usr_cmd.search_str);
		head = insertEnd(head, line_buffer, is_str_in_line, line_count, line_size);
		line_size = getline(&line_buffer, &line_buffer_size, fp);
	}

	fclose(fp);
	freeList(head);
	freeCommand(&usr_cmd);

	return 0;
}
