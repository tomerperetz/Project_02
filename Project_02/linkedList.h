#ifndef LINKED_LIS_H
#define LINKED_LIST_H
// Public Stractures --------------------------------------------------------------------->

typedef struct _node
{
	int data;
	struct _node *prev;
	struct _node *next;
} node;

// Public Functions ---------------------------------------------------------------------->

node* insert_start(node *head, int data);

node *insert_end(node *head, int data);

int add_after_element(node *head, int element, int data);

void printElementIdx(node *head, int element);

void printList(node *head);

node* freeList(node *head);

node* del_idx(node *head, int idx, int *exit_flag);

#endif
