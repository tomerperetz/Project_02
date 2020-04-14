/*
====================================================================================================================
Description:
this lib is used for parsering functions.
====================================================================================================================
*/

// Includes ---------------------------------------------------------------------->
#include "errorHandler.h"
#include "parser.h"



// Private Functions ---------------------------------------------------------------------->
char* FindNextWordBegining(char* string_ptr) {
	int idx = 0;

	for (idx = 0; string_ptr[idx] != '\0'; idx++) {
		if (string_ptr[idx] != ' ' && string_ptr[idx] != '	')
			continue;
		else
			break;

	}
	for (idx = idx; string_ptr[idx] != '\0'; idx++) {
		if (string_ptr[idx] == ' ' || string_ptr[idx] == '	')
			continue;
		else
			return &string_ptr[idx];
	}
	raiseError(5, __FILE__, __func__, __LINE__, ERR_5_NOT_ENOUGH_VALUES);
	return NULL;
}

int CheckAction(char *action_string) {
	size_t idx = 0;
	char action_type[MAX_LINE_LEN] = "";

	for (idx = 0; idx < strlen(action_string); idx++) {
		if (action_string[idx] == '\0' || action_string[idx] == '\n') {
			action_type[idx] = '\0';
			break;
		}
		if (action_string[idx] != ' ' && action_string[idx] != '	')
			action_type[idx] = action_string[idx];
		else {
			action_type[idx] = '\0';
			break;
		}
	}
	if (strcmp(action_type, "add_end") == 0) return ADD_END;
	else if (strcmp(action_type, "add_start") == 0) return ADD_START;
	else if (strcmp(action_type, "add_after") == 0) return ADD_AFTER;
	else if (strcmp(action_type, "index") == 0) return INDEX;
	else if (strcmp(action_type, "del") == 0) return DEL;
	else if (strcmp(action_type, "print") == 0) return PRINT;
	else if (strcmp(action_type, "exit") == 0) return EXIT;
	else {
		raiseError(3, __FILE__, __func__, __LINE__, ERR_3_ACTION_NOT_DEFINED);
		return NO_ACTION;
	}
}

int CheckNumber(char *number_string, int* exit_flag) {
	int value;
	size_t idx = 0;
	char string_number_copy[LONGEST_INT_SIZE] = "";

	for (idx = 0; idx < strlen(number_string); idx++) {
		if (number_string[idx] == '\0') {
			string_number_copy[idx] = number_string[idx];
			break;
		}
		if ((number_string[idx] <= ASCI_NUMBER_FOR_9 && number_string[idx] >= ASCI_NUMBER_FOR_0) || (number_string[idx] == '-'))
			string_number_copy[idx] = number_string[idx];
		else {
			string_number_copy[idx] = '\0';
			break;
		}
	}
	if (strcmp(string_number_copy, "0") == 0) return 0;     // because atoi() returns 0 for invalid input and 0 is a valid input for this function- we need to check it. 
	value = atoi(string_number_copy);
	if (value == 0) {
		raiseError(4, __FILE__, __func__, __LINE__, ERR_4_NUMBER_NOT_DEFINED);
		*exit_flag = ERR;
		return ERR;
	}
	else
		return value;
}

void UpperToLowerCase(char *action_string) {
	size_t idx = 0;

	for (idx = 0; idx < strlen(action_string); idx++) {
		action_string[idx] = tolower(action_string[idx]);
	}
}




// Public Functions ---------------------------------------------------------------------->
void InitializeCommand(command *input_command) {
	input_command->file_path = NULL;
	input_command->search_str = NULL;
	input_command->enabled.A = FALSE;
	input_command->enabled.A_num = FALSE;
	input_command->enabled.b = FALSE;
	input_command->enabled.c = FALSE;
	input_command->enabled.E = FALSE;
	input_command->enabled.i = FALSE;
	input_command->enabled.n = FALSE;
	input_command->enabled.v = FALSE;
	input_command->enabled.x = FALSE;

}

void PrintCommand(command input_command) {
	if (input_command.search_str != NULL) {

	}
}

//// main Function ---------------------------------------------------------------------->
//int main() {
//	int argc = 4;
//	char argv[][20] = { "grep", "-n", "blabla","text.txt" };
//	command input_command;
//
//	InitializeCommand(&input_command);
//
//
//}