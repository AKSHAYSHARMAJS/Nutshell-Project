#ifndef LL_H
#define LL_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	char *data;
	char *node_name;
	struct node *next;
} node;


typedef struct LL{
	struct node *start;
	struct node *end;
} LL;

LL *create_LL();

void push_LL(LL *list, char *name, char *data);

void print_LL(LL *list);

char *command_expand(LL *list, char *name);

char *expand_with_recursion(LL *list, LL *recursionlist, char *cmdvalue);

void remove_node(LL *list, char *name);

#endif
