#ifndef LINKED_LIS_H
#define LINKED_LIST_H

#include <stdbool.h>

// Public Stractures --------------------------------------------------------------------->

typedef struct _node
{
	char *line;
	bool is_str_in_line;
	int line_number;
	int byte_number;
	int line_length;
	struct _node *prev;
	struct _node *next;
} node;

// Public Functions ---------------------------------------------------------------------->

node *insert_end(node *head, const char* line, const bool is_str_in_line, const int line_number);

void printList(node *head);

node* freeList(node *head);


#endif
