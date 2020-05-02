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
#define ERR_LINKED_LIST_EMPTY_ID 3
#define ERR_LINKED_LIST_EMPTY_CONTENT "Linked list is empty.\n"
#define ERR_ILLEGAL_STRING_ID 4
#define ERR_ILLEGAL_STRING__CONTENT "Illegal input string detected! please try again.\n"

void raiseError(int error_id, const char *file_path, const char *function_name, int line, const char *description);


#endif 