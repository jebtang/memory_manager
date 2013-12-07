#include "memory_monitor.h"
/*  * b-tree.c  *  *  Created on: Nov 16, 2013  *      Author: ravitandon  */ 
#include <iostream>
#include "b-tree.h"
#include "stdio.h"
#include "math.h"
#include <time.h>
#include <stdlib.h>
#include "stdbool.h"
using namespace std;

void init (){

}

void finish (){
  print_memory();
}

struct node *create_tree (int num_nodes, int branching_factor, int *values){
	struct node *root = (struct node *) malloc (sizeof (struct node));
	root->value = values[0];
	int count;
	for (count = 1; count < num_nodes; count++){
		insert_tree (root, values[count]);
	}
	return root;
}
/*void create_children (int height, struct node *node, int maxHeight){
	if (height < maxHeight){
		srand(time(NULL));
		node->left = (struct node *) malloc (sizeof (struct node));
access ((void *)		node ,1);
		node->left->value = 2*(node->value);
access ((void *)		node ,1);
access ((void *)left ,1);
access ((void *)node ,1);
		node->right = (struct node *) malloc (sizeof (struct node));
access ((void *)		node ,1);
		node->right->value = 2*(node->value) + 1;
access ((void *)		node ,1);
access ((void *)right ,1);
access ((void *)node ,1);
		create_children (height+1, node->left, maxHeight);
access ((void *)node ,1);
		create_children (height+1, node->right, maxHeight);
access ((void *)node ,1);
	}
	}*/

void print_tree_in_order (struct node *node){
	if (node != NULL){
		printf("%d\t", node->value);
		access ((void *)node ,1);
		print_tree_in_order (node->left);
		access ((void *)node ,1);
		print_tree_in_order (node->right);
		access ((void *)node ,1);
	}
}

void print_tree_pre_order (struct node *node){
	if (node != NULL){
		print_tree_pre_order (node->left);
		access ((void *)node ,1);
		printf("%d\t", node->value);
		access ((void *)node ,1);
		print_tree_pre_order (node->right);
		access ((void *)node ,1);
	}
}

bool search_tree (int value, struct node*node){
	if (node == null){
		return false;
	}
	if (node-> value == value) 		return true;
	access ((void *)node ,1);
	if (node->value < value){
	  access ((void *)node ,1);
		return (search_tree (value, node->left));
		access ((void *)node ,1);
	} else {
		return (search_tree(value, node->right));
		access ((void *)node ,1);
	}
}

void update_tree (struct node*node, int old_value, int new_value){
if (node != null){
	if (node->value == old_value){
	  access ((void *)node ,1);
		node->value = new_value;
		access ((void *)		node ,1);
	} else {
		if (node->value > old_value){
		  access ((void *)node ,1);
			update_tree (node->left, old_value, new_value);
			access ((void *)node ,1);
		} else {
		  update_tree (node->right, old_value, new_value);
		  access ((void *)node ,1);
		}
	}
}
}

struct node *create_node (int value){
	struct node *new_node = (struct node *) malloc (sizeof (struct node));
	new_node->value = value;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}
void insert_tree (struct node*node, int value){
	if (node != null){
		if (node->value > value){
		  //access ((void *)node ,1);
			if (node->left == null){
			 node->left = create_node (value);
			 access ((void *) node ,3);
			} else {
			 insert_tree (node->left, value);
			 access ((void *)node ,2);
			}
		} else {
			if (node->value < value){
			  //access ((void *)node ,1);
				if (node->right == null){
				  //access ((void *)node ,3);
					node->right = create_node (value);
					access ((void *)node ,3);
				} else {
					insert_tree (node->right, value);
					access ((void *)node ,2);
				}
			}
		}
	}
}
