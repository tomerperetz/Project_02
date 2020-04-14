/*
====================================================================================================================
Description:
this lib is used for error handeling.
====================================================================================================================
*/

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#define ERR -1
#define ERR_IO_ID 1
#define ERR_IO_CONTENT "IO Error! Please restart the program.\n"
#define ERR_MEM_ALLOC_ID 2
#define ERR_MEM_ALLOC_CONTENT "Memory allocation failed. Exiting program.\n"


void raiseError(int error_id, const char *file_path, const char *function_name, int line, const char *description);


#endif //ERROR_HANDLER_H