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
#define ERR_2_MEM_ALLOC "Memory allocation failed. Exiting program.\n"
#define ERR_3_ACTION_NOT_DEFINED "This is not a valid action. Exiting program.\n"
#define ERR_4_NUMBER_NOT_DEFINED "Not a valid number input. Exiting program.\n"
#define ERR_5_NOT_ENOUGH_VALUES "Not enough values. Exiting program.\n"

void raiseError(int error_id, const char *file_path, const char *function_name, int line, const char *description);


#endif //ERROR_HANDLER_H