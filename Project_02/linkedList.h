#ifndef LINKED_LIS_H
#define LINKED_LIST_H

#include <stdbool.h>

// Public Stractures --------------------------------------------------------------------->

typedef struct _node
{
	char *line;
	bool match;
	int line_number;
	int byte_number;
	int line_length;
	struct _node *prev;
	struct _node *next;
} node;

// Public Functions ---------------------------------------------------------------------->

node* insertEnd(node *head, const char* line, const int line_number, const int line_size);

void printList(node *head);

node* freeList(node *head);


#endif
