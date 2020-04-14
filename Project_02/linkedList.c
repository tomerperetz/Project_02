
/*
====================================================================================================================
Description:
this lib is used for handeling linked lists
====================================================================================================================
*/

// Includes ---------------------------------------------------------------------->
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errorHandler.h"
#include "linkedList.h"


// Private Functions ---------------------------------------------------------------------->

node* initNode(const char* line, const bool is_str_in_line, const int line_number)
{
	node *new_node = (node*)malloc(sizeof(node));
	int line_len = 0;
	if (new_node == NULL)
	{
		raiseError(ERR_MEM_ALLOC_ID, __FILE__, __func__, __LINE__, ERR_MEM_ALLOC_CONTENT);
		return NULL;
	}

	line_len = strlen(line);
	new_node->line = (char*)malloc(sizeof(char)*line_len);
	strcpy(new_node->line, line);
	new_node->is_str_in_line = is_str_in_line;
	new_node->line_number = line_number;
	new_node->byte_number = 0;
	new_node->line_length = line_len;
	new_node->prev = NULL;
	new_node->next = NULL;

	return new_node;
}

// Public Functions ---------------------------------------------------------------------->

node* insertEnd(node *head, const char* line, const bool is_str_in_line, const int line_number)
{
	node *new_node = initNode(line, is_str_in_line, line_number);
	node *curr_node = head;

	// if the list is currently empty
	if (curr_node == NULL)
		return new_node;

	// else - search the for the last item
	while (curr_node->next != NULL)
		curr_node = curr_node->next;

	curr_node->next = new_node;
	new_node->prev = curr_node;

	// update number of bytes
	new_node->byte_number = new_node->prev->line_length + new_node->prev->byte_number;
	
	return head;
}

void printList(node *head)
{
	node *curr_node = head;
	if (head == NULL)
		printf("List is empty\n");
	
	else
	{
		while (curr_node != NULL)
		{
			printf("line number: %d\n", curr_node->line_number);
			printf("line: %s", curr_node->line);
			printf("line length in chars: %d\n", curr_node->line_length);
			printf("line length bytes: %d\n", curr_node->byte_number);
			printf("str in line: %d\n", curr_node->is_str_in_line);
			curr_node = curr_node->next;
		}
	}
	return;
}

node* freeList(node *head)
{
	node *temp;
	node *curr_node = head;
	while (curr_node != NULL)
	{
		temp = curr_node->next;
		free(curr_node->line);
		free(curr_node);
		curr_node = temp;
	}

	return NULL;
}

