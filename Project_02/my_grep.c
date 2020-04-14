#include <stdlib.h>
#include <stdio.h>  
#include "errorHandler.h"

// Dummy Variables
#define TEST_FILE_NAME "my_text.txt"


int main()
{
	char *line_buffer = NULL;
	size_t line_buffer_size = 0;
	int line_count = 0;
	int byte_count = 0;
	size_t line_size;
	FILE *fp = fopen(TEST_FILE_NAME, "r");
	
	if (!fp)
	{
		fprintf(stderr, "Error opening file '%s'\n", TEST_FILE_NAME);
		//raiseError(ERR_IO_ID, __FILE__, __func__, __LINE__, ERR_IO_CONTENT);
		return EXIT_FAILURE;
	}

	line_size = getline(&line_buffer, &line_buffer_size, fp);

	printf("this is the first line:\n");
	printf("%s", line_buffer);

	return 0;
}
