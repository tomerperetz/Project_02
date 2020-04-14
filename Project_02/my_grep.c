#include <stdlib.h>
#include <stdio.h>  
#include <string.h>
#include "errorHandler.h"
#include "linkedList.h"

// Dummy Variables
#define TEST_FILE_NAME "my_text.txt"
#define NEEDLE "hump"

bool isLineMatch(const char *heist, const char *needle)
{
	if (strstr(heist, needle) != NULL) return true;
	return false;
}

int main()
{
	node *head = NULL;
	char *line_buffer = NULL;
	size_t line_buffer_size = 0;
	size_t line_size;
	FILE *fp = fopen(TEST_FILE_NAME, "r");
	int line_count = 0;
	bool is_str_in_line;

	if (!fp)
	{
		fprintf(stderr, "Error opening file '%s'\n", TEST_FILE_NAME);
		raiseError(ERR_IO_ID, __FILE__, __func__, __LINE__, ERR_IO_CONTENT);
		return EXIT_FAILURE;
	}

	line_size = getline(&line_buffer, &line_buffer_size, fp);

	while (line_size != EOF)
	{
		line_count++;
		is_str_in_line = isLineMatch(line_buffer, NEEDLE);
		head = insertEnd(head, line_buffer, is_str_in_line, line_count);
		line_size = getline(&line_buffer, &line_buffer_size, fp);
	}

	fclose(fp);
	printList(head);
	freeList(head);

	return 0;
}
