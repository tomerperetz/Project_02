
/*
====================================================================================================================
Description:
this lib is used for error handeling.
====================================================================================================================
*/

// Includes -------------------------------------------------------------------------------------->
#include <stdio.h>
#include "errorHandler.h"

// Public Functions -------------------------------------------------------------------------------------- >
void raiseError(int error_id, const char *file_path, const char *function_name, int line, const char *description)
{
	/*
	Description: Error handling function.
				prints error description and location and exists the program.
	*/

	printf("=====================================================================\n");
	printf("FATAL ERROR: ERROR NUMBER %d\n", error_id);
	printf("File: %s\n", file_path);
	printf("Function: %s\n", function_name);
	printf("Line: %d\n", line);
	printf("Description: %s", description);
	printf("=====================================================================\n");
}
