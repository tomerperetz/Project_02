
/*
====================================================================================================================
Description:
this lib is used for handeling linked lists
====================================================================================================================
*/

// Includes ---------------------------------------------------------------------->
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "errorHandler.h"
#include "linkedList.h"


// Private Functions ---------------------------------------------------------------------->

node* init_node(int data)
{
	node *new_node = (node*)malloc(sizeof(node));

	if (new_node == NULL)
	{
		raiseError(2, __FILE__, __func__, __LINE__, ERR_2_MEM_ALLOC);
		return NULL;
	}
	new_node->data = data;
	new_node->next = NULL;
	new_node->prev = NULL;

	return new_node;
}

int isListEmpty(node *head)
{
	// check if list is empty a given head node, if so - raise errors
	if (head == NULL)
	{
		raiseError(1, __FILE__, __func__, __LINE__, ERR_1_LINKED_LIST_ERR);
		return TRUE;
	}
	return FALSE;
}

node* find_node_by_index(node *head, int idx)
{
	node* curr_node = head;
	int i = 0;

	if (isListEmpty(curr_node)) return NULL;

	for (i = 0; i < idx; i++)
	{
		if (isListEmpty(curr_node->next)) return NULL;
		curr_node = curr_node->next;
	}

	return curr_node;
}

node* find_node_by_data_ret_node(node *head, int element)
{
	node* curr_node = head;
	while (curr_node != NULL)
	{
		if (curr_node->data == element) return curr_node;
		curr_node = curr_node->next;
	}
	raiseError(1, __FILE__, __func__, __LINE__, ERR_1_LINKED_LIST_ERR);
	return NULL;
}

int find_node_by_data_ret_idx(node *head, int element)
{
	node* curr_node = head;
	int idx = 0;
	while (curr_node != NULL)
	{
		if (curr_node->data == element) return idx;
		idx++;
		curr_node = curr_node->next;
	}
	return ERR;
}


// Public Functions ---------------------------------------------------------------------->
node* insert_start(node *head, int data)
{
	// Description: insert item to the head of the list
	node *new_node = init_node(data);
	if (head != NULL)
		head->prev = new_node;
	new_node->next = head;
	return new_node;
}

node* insert_end(node *head, int data)
{
	node *new_node = init_node(data);
	node *curr_node = head;

	// if the list is currently empty
	if (curr_node == NULL)
		return new_node;

	// else - search the for the last item
	while (curr_node->next != NULL)
		curr_node = curr_node->next;

	curr_node->next = new_node;
	new_node->prev = curr_node;
	return head;
}

int add_after_element(node *head, int element, int data)
{
	node *new_node = init_node(data);
	node *element_node = find_node_by_data_ret_node(head, element);
	node *temp_node;

	if (element_node == NULL) return ERR;

	temp_node = element_node->next;
	element_node->next = new_node;
	new_node->next = temp_node;

	if (temp_node != NULL)
		temp_node->prev = new_node;

	return TRUE;
}

void printElementIdx(node *head, int element) {
	int element_idx = find_node_by_data_ret_idx(head, element);

	if (element_idx != ERR)
		printf("%d\n", element_idx);
	else
		printf("%d\n", ERR);
}

node* del_idx(node *head, int idx, int *exit_flag)
{
	node *quarntine_node = find_node_by_index(head, idx);
	node *prev_node = NULL, *next_node = NULL;
	node *new_head = head;

	if (quarntine_node == NULL)
	{
		printf("111111\n");
		*exit_flag = ERR;
		return NULL;
	}

	prev_node = quarntine_node->prev;
	next_node = quarntine_node->next;
	if (next_node != NULL)
		next_node->prev = prev_node;
	if (prev_node != NULL)
		prev_node->next = next_node;
	else
		new_head = next_node;

	free(quarntine_node);

	return new_head;
}

void printList(node *head)
{
	node *curr_node = head;
	if (head == NULL)
		printf("[]\n");
	else
	{
		printf("[");
		while (curr_node->next != NULL)
		{
			printf("%d ,", curr_node->data);
			curr_node = curr_node->next;
		}

		printf("%d]\n", curr_node->data);
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
		free(curr_node);
		curr_node = temp;
	}

	return NULL;
}

