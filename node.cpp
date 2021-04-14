#include "node.h"

LL * create_LL() {
	LL *list = new LL;
	list->start = NULL;
	list->end = NULL;
	return list;
}

void push_LL(LL *list, char *name, char *data) {
	if(strcmp(name, data) == 0){
		printf("Error, expansion of \"%s\" would create a loop.\n", name);
		return;
	}
    node *new_node = new node;
  	new_node->data = data;
  	new_node->node_name = name;
  	new_node->next = NULL;

  	node *curr_alias = new node;
  	curr_alias = list->start;

    int addNode = 1;

    while(curr_alias != NULL)
    {
    		if(strcmp(curr_alias->node_name, name) == 0)
        {
    			addNode = 0;
    			break;
    		}
    		curr_alias = curr_alias->next;
  	}
  	if (!addNode)
    {
  		curr_alias->data = data;
  	}
    else if (list->start != NULL)
    {
  		list->end->next = new_node;
  		list->end = new_node;
  	}
    else
    {
  		list->start = new_node;
  		list->end = new_node;
  	}
}


void print_LL(LL *list){
	node * curr_node = list->start;
	while (curr_node != NULL) {
		printf("%s=%s\n",curr_node->node_name, curr_node->data);
		curr_node = curr_node->next;
	}
}


char *command_expand(LL *list, char *name) {
	node *curr_list = new node;
	curr_list = list->start;
	int exist = 0;
	char *cmdvalue = "Command not found";
	while (curr_list != NULL) {
		if(strcmp(curr_list->node_name, name) == 0) {
			cmdvalue = curr_list->data;
			exist = 1;
			break;
		}
		curr_list = curr_list->next;
	}
	if (exist) {
		LL *recursionlist = create_LL();
		push_LL(recursionlist, curr_list->node_name, curr_list->data);
		char *newvalue = expand_with_recursion(list, recursionlist, cmdvalue);
		return newvalue;
	}
	return cmdvalue;
}


char *expand_with_recursion(LL *list, LL *recursionlist, char *cmdvalue) {
	node *curr_list = new node;
	curr_list = list->start;
	node *recursiontrack = new node;
	recursiontrack = recursionlist->start;

	char* newcmd = new typeof(cmdvalue)[sizeof(cmdvalue)];
	newcmd = cmdvalue;
	int length = strlen(cmdvalue);
	int whitespaces = 0;
	for (int i = 0; i < length; i++) {
		if (cmdvalue[i] == ' ') {
			whitespaces++;
		}
	}
	if (whitespaces == 0) {
		while(recursiontrack != NULL) {
			if (strcmp(recursiontrack->node_name, newcmd) == 0) {
				strcat("Error, expansion of ", newcmd);
				strcat(newcmd," command would create a loop.\n");
				return newcmd;
			} else {
				recursiontrack = recursiontrack->next;
			}
		}
		while (curr_list != NULL) {
			if (strcmp(curr_list->node_name, cmdvalue) == 0){
				newcmd = curr_list->data;
				push_LL(recursionlist, curr_list->node_name, curr_list->data);
				cmdvalue = expand_with_recursion(list, recursionlist, newcmd);
				newcmd = cmdvalue;
				return cmdvalue;
			} else{
				curr_list = curr_list->next;
			}
		}
		return newcmd;
	}

	char *subcmd = new typeof(cmdvalue)[sizeof(cmdvalue)];
	char *remaining = new typeof(cmdvalue)[sizeof(cmdvalue)];
	int cmdlength = 0;

	for (int i = 0; i < length; i++) {
		cmdlength++;
		if (cmdvalue[i] == ' ') {
			for (int j = 0; j < cmdlength; j++) {
				subcmd[j] = cmdvalue[j];
			}
			int h = 0;
			for (int j = cmdlength; j < length; j++) {
				remaining[h++] = cmdvalue[j];
			}
			break;
		}
	}
	char* rebuild_cmd = new typeof(cmdvalue)[sizeof(cmdvalue)];
	curr_list = list->start;
	char* val = new typeof(cmdvalue)[sizeof(cmdvalue)];
	while(curr_list != NULL) {
		if(strcmp(curr_list->node_name, subcmd) == 0) {
			for(int z = 0; z < strlen(curr_list->data); z++) {
				val[z] = curr_list->data[z];
			}
			while(recursiontrack != NULL) {
				if (strcmp(recursiontrack->node_name, subcmd) == 0) {
					strcat("Error, expansion of ", subcmd);
					strcat(subcmd," command would create a loop.\n");
					return subcmd;
				} else {
					recursiontrack = recursiontrack->next;
				}
			}
			push_LL(recursionlist, curr_list->node_name, curr_list->data);
			rebuild_cmd = expand_with_recursion(list, recursionlist, val);
			strcat(rebuild_cmd, " ");
			strcat(rebuild_cmd, remaining);
			return rebuild_cmd;
		}
		curr_list = curr_list->next;
	}
	return cmdvalue;
}


void remove_node(LL *list, char *name) {
	node *curr_node = list->start;
	node *prev_node = NULL;
	int index = 0;
	int length = 0;
	while (curr_node != NULL) {
		length++;
		curr_node = curr_node->next;
	}
	curr_node = list->start;

	while (curr_node != NULL) {
		char *nodeName = curr_node->node_name;
		if ( strcmp(nodeName, name) == 0 ) {
			break;
		} else {
			prev_node = curr_node;
			curr_node = curr_node->next;
			index++;
		}
	}
	if(curr_node != NULL) {
		if (index == 0) {
			prev_node = curr_node->next;
			list->start = prev_node;
		} else if (index == length) {
			list->end = prev_node;
			prev_node->next = curr_node->next;
		} else {
			prev_node->next = curr_node->next;
		}
		curr_node->next = NULL;
		free(curr_node);
	}
}
