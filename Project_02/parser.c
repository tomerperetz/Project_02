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
		input_command->enabled.print_extra_lines = true;
		if (argument[2] != '\0') {
			input_command->enabled.num_of_extra_lines = atoi(argument + 2);
		}
		else {
			*A_flag = true;
		}
		break;
	case 'b':
		input_command->enabled.print_bytes = true;
		break;
	case 'c':
		input_command->enabled.print_count_only = true;
		break;
	case 'E':
		input_command->enabled.extended_regexp = true;
		break;
	case 'i':
		input_command->enabled.match_case = false;
		break;
	case 'n':
		input_command->enabled.print_line_number = true;
		break;
	case 'v':
		input_command->enabled.invert_match = true;
		break;
	case 'x':
		input_command->enabled.wrap_around = false;
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
	input_command->enabled.print_extra_lines = false;
	input_command->enabled.num_of_extra_lines = false;
	input_command->enabled.print_bytes = false;
	input_command->enabled.print_count_only = false;
	input_command->enabled.extended_regexp = false;
	input_command->enabled.match_case = true;
	input_command->enabled.print_line_number = false;
	input_command->enabled.invert_match = false;
	input_command->enabled.wrap_around = true;
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
	printf("Grep option print_extra_lines:			%d   with num: %d\n", input_command.enabled.print_extra_lines, input_command.enabled.num_of_extra_lines);
	printf("Grep option print_bytes:                %d\n", input_command.enabled.print_bytes);
	printf("Grep option print_count_only:           %d\n", input_command.enabled.print_count_only);
	printf("Grep option extended_regexp:            %d\n", input_command.enabled.extended_regexp);
	printf("Grep option match_case:					%d\n", input_command.enabled.match_case);
	printf("Grep option print_line_number:          %d\n", input_command.enabled.print_line_number);
	printf("Grep option invert_match:               %d\n", input_command.enabled.invert_match);
	printf("Grep option wrap_around:                %d\n", input_command.enabled.wrap_around);
	printf("Input through stdin:					%d\n", input_command.std_in);
}

int commandParser(char **arguments_list, int arguments_amount, command *input_command) {
	int idx = 2, A_flag = false, search_str_flag = false, file_path_flag = false;


	for (idx = 1; idx < arguments_amount; idx++) {
		if (A_flag == true) {
			input_command->enabled.num_of_extra_lines = atoi(arguments_list[idx]);
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

void freeCommand(command *input_command) {
	if (input_command->search_str != NULL) {
		free((input_command->search_str));
	}
	if (input_command->file_path != NULL) {
		free(input_command->file_path);
	}
}

