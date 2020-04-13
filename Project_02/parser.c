/*
====================================================================================================================
Description:
this lib is used for parsering and has the main() function.
====================================================================================================================
*/

// Includes ---------------------------------------------------------------------->
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "linkedList.h"
#include "errorHandler.h"

// Defines ---------------------------------------------------------------------->
#define MAX_LINE_LEN 100
#define LONGEST_INT_SIZE 11
#define ADD_END 1
#define ADD_START 2
#define ADD_AFTER 3
#define INDEX 4
#define DEL 5
#define PRINT 6
#define EXIT 7
#define NO_ACTION 8
#define ASCI_NUMBER_FOR_0 48
#define ASCI_NUMBER_FOR_9 57

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

// main Function ---------------------------------------------------------------------->
int main() {

}
