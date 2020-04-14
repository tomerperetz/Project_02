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
void upperToLowerCase(char *action_string) {
	size_t idx = 0;

	for (idx = 0; idx < strlen(action_string); idx++) {
		action_string[idx] = tolower(action_string[idx]);
	}
}

void checkGrepOption(char *argument, command* input_command, int *A_flag) {
	switch (argument[1]) {
	case 'A':
		input_command->enabled.A = true;
		if (argument[2] != '\0') {
			input_command->enabled.A_num = atoi(argument + 2);
		}
		else {
			*A_flag = true;
		}
		break;
	case 'b':
		input_command->enabled.b = true;
		break;
	case 'c':
		input_command->enabled.c = true;
		break;
	case 'E':
		input_command->enabled.E = true;
		break;
	case 'i':
		input_command->enabled.i = true;
		break;
	case 'n':
		input_command->enabled.n = true;
		break;
	case 'v':
		input_command->enabled.v = true;
		break;
	case 'x':
		input_command->enabled.x = true;
		break;
	}

}

char* insertStrToCommand(char *detination_str, char *argument) {
	size_t idx =0, str_size = 0;

	str_size = strlen(argument) + 1;
	detination_str = (char*)malloc(sizeof(char)*str_size);
	if (detination_str == NULL) {
		raiseError(ERR_MEM_ALLOC_ID, __FILE__, __func__, __LINE__, ERR_MEM_ALLOC_CONTENT);
		return NULL;
	}
	//strcpy(detination_str, argument);
	for (idx = 0; idx < str_size; idx++) {
		detination_str[idx] = argument[idx];
		if (detination_str[idx] == '\n') {
			detination_str[idx] = '\0';
		}
	}
	return detination_str;

}

// Public Functions ---------------------------------------------------------------------->
void initializeCommand(command *input_command) {
	input_command->search_str = NULL;
	input_command->file_path = NULL;
	input_command->enabled.A = false;
	input_command->enabled.A_num = false;
	input_command->enabled.b = false;
	input_command->enabled.c = false;
	input_command->enabled.E = false;
	input_command->enabled.i = false;
	input_command->enabled.n = false;
	input_command->enabled.v = false;
	input_command->enabled.x = false;
	input_command->std_in = false;

}

void printCommand(command input_command) {
	if (input_command.search_str == NULL) {
		printf("Search string is:            NULL\n");
	}
	else {
		printf("Search string is:            %s\n", input_command.search_str);
	}
	if (input_command.std_in == false) {
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
	int idx = 2, A_flag = false, search_str_flag = false, file_path_flag = false;


	for (idx = 1; idx < arguments_amount; idx++) {
		if (A_flag == true) {
			input_command->enabled.A_num = atoi(arguments_list[idx]);
			A_flag = false;
			continue;
		}
		if (arguments_list[idx][0] == '-') {
			checkGrepOption(arguments_list[idx], input_command, &A_flag);
		}
		else {
			if (search_str_flag == false) {
				input_command->search_str = insertStrToCommand(input_command->search_str, arguments_list[idx]);
				if (input_command->search_str == NULL) {
					return false;
				}
				search_str_flag = true;
				continue;
			}
			else {
				input_command->file_path = insertStrToCommand(input_command->file_path, arguments_list[idx]);
				if (input_command->file_path == NULL) {
					return false;
				}
				file_path_flag = true;
				break;
			}
		}
	}
	if (file_path_flag == false) {          // check if there is a better way to do it. 
		input_command->std_in = true;
	}
	return true;
}

void freeAllMemorey(command *input_command) {
	if (input_command->search_str != NULL) {
		free((input_command->search_str));
	}
	if (input_command->file_path != NULL) {
		free(input_command->file_path);
	}
}

