
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

node* initNode(const char* line, const int line_number, const int line_size)
{
	node *new_node = (node*)malloc(sizeof(node));
	if (new_node == NULL)
	{
		raiseError(ERR_MEM_ALLOC_ID, __FILE__, __func__, __LINE__, ERR_MEM_ALLOC_CONTENT);
		return NULL;
	}

	new_node->line = (char*)malloc(sizeof(char)*line_size + 1);
	strcpy(new_node->line, line);
	if(new_node->line[line_size-1] == '\n')
		new_node->line[line_size-1] = '\0';
	new_node->match = false;
	new_node->line_number = line_number;
	new_node->byte_number = 0;
	new_node->line_length = line_size;
	new_node->prev = NULL;
	new_node->next = NULL;

	return new_node;
}

// Public Functions ---------------------------------------------------------------------->

node* insertEnd(node *head, const char* line, const int line_number, const int line_size)
{
	node *new_node = initNode(line, line_number, line_size);
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
			printf("line: %s\n", curr_node->line);
			printf("line length in chars: %d\n", curr_node->line_length);
			printf("line length bytes: %d\n", curr_node->byte_number);
			printf("str in line: %d\n", curr_node->match);
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

