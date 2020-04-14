/*
====================================================================================================================
Description:
this lib is used for parsering functions.
====================================================================================================================
*/

// Includes ------------------------------------------------------------------------------->
#include "errorHandler.h"
#include "parser.h"



// Private Functions ---------------------------------------------------------------------->
char* findNextWordBegining(char* string_ptr) {
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

int checkAction(char *action_string) {
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

int checkNumber(char *number_string, int* exit_flag) {
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

void upperToLowerCase(char *action_string) {
	size_t idx = 0;

	for (idx = 0; idx < strlen(action_string); idx++) {
		action_string[idx] = tolower(action_string[idx]);
	}
}

void checkGrepOption(char *argument, command* input_command, int *A_flag) {
	switch (argument[1]) {
	case 'A':
		input_command->enabled.A = TRUE;
		if (argument[2] != '\0') {
			input_command->enabled.A_num = atoi(argument + 2);
		}
		else {
			*A_flag = TRUE;
		}
		break;
	case 'b':
		input_command->enabled.b = TRUE;
		break;
	case 'c':
		input_command->enabled.c = TRUE;
		break;
	case 'E':
		input_command->enabled.E = TRUE;
		break;
	case 'i':
		input_command->enabled.i = TRUE;
		break;
	case 'n':
		input_command->enabled.n = TRUE;
		break;
	case 'v':
		input_command->enabled.v = TRUE;
		break;
	case 'x':
		input_command->enabled.x = TRUE;
		break;
	}

}

char* insertStrToCommand(char *detination_str, char *argument) {
	size_t str_size = 0;

	str_size = strlen(argument) + 1;
	detination_str = (char*)malloc(sizeof(char)*str_size);
	if (detination_str == NULL) {
		raiseError(2, __FILE__, __func__, __LINE__, ERR_2_MEM_ALLOC);
		return NULL;
	}
	strcpy_s(detination_str, str_size, argument);
	return detination_str;

}

// Public Functions ---------------------------------------------------------------------->
void initializeCommand(command *input_command) {
	input_command->file_path;
	input_command->search_str;
	input_command->enabled.A = FALSE;
	input_command->enabled.A_num = FALSE;
	input_command->enabled.b = FALSE;
	input_command->enabled.c = FALSE;
	input_command->enabled.E = FALSE;
	input_command->enabled.i = FALSE;
	input_command->enabled.n = FALSE;
	input_command->enabled.v = FALSE;
	input_command->enabled.x = FALSE;
	input_command->std_in = FALSE;

}

void printCommand(command input_command) {
	if (input_command.search_str == NULL) {
		printf("Search string is:            NULL\n");
	}
	else {
		printf("Search string is:            %s\n", input_command.search_str);
	}
	if (input_command.file_path == NULL) {
		printf("File path is:                NULL\n");
	}
	else {
		printf("File path is:                %s\n", input_command.file_path);
	}
	printf("Grep option A: %d   with num: %d\n", input_command.enabled.A, input_command.enabled.A_num);
	printf("Grep option b:               %d\n", input_command.enabled.b);
	printf("Grep option c:               %d\n", input_command.enabled.c);
	printf("Grep option E:               %d\n", input_command.enabled.E);
	printf("Grep option i:               %d\n", input_command.enabled.i);
	printf("Grep option n:               %d\n", input_command.enabled.n);
	printf("Grep option v:               %d\n", input_command.enabled.v);
	printf("Grep option x:               %d\n", input_command.enabled.x);
	printf("Input through stdin:         %d\n", input_command.std_in);
}

int commandParser(char **arguments_list, int arguments_amount, command *input_command) {
	int idx = 2, parsin_flag = 0, A_flag = FALSE, search_str_flag = FALSE, file_path_flag = FALSE;


	for (idx = 2; idx < arguments_amount; idx++) {
		if (A_flag == TRUE) {
			input_command->enabled.A_num = atoi(arguments_list[idx]);
			A_flag = FALSE;
			continue;
		}
		if (arguments_list[idx][0] == '-') {
			checkGrepOption(arguments_list[idx], input_command, &A_flag);
		}
		else {
			if (search_str_flag == FALSE) {
				input_command->search_str = insertStrToCommand(input_command->search_str, arguments_list[idx]);
				if (input_command->search_str == NULL) {
					return FALSE;
				}
				search_str_flag = TRUE;
				continue;
			}
			else {
				input_command->file_path = insertStrToCommand(input_command->file_path, arguments_list[idx]);
				if (input_command->file_path == NULL) {
					return FALSE;
				}
				file_path_flag = TRUE;
				break;
			}
		}
	}
	if (file_path_flag = FALSE) {          // check if there is a better way to do it. 
		input_command->std_in = TRUE;
	}
	return TRUE;
}

void freeAllMemorey(command *input_command) {
	if (input_command->search_str != NULL) {
		free((input_command->search_str));
	}
	if (input_command->file_path != NULL) {
		free(input_command->file_path);
	}
}

// main Function ---------------------------------------------------------------------->
