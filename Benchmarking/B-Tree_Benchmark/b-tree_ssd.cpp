/*
 * b-tree.c
 *
 *  Created on: Nov 16, 2013
 *      Author: ravitandon
 */

#include "b-tree.h"
#include "stdio.h"
#include "math.h"
#include <time.h>
#include <stdlib.h>
#include "stdbool.h"
#include "../../ssd_alloc.h"

struct node *create_tree (int num_nodes, int branching_factor, int *values){
	struct node *root = (struct node *) ssd_oalloc (1, sizeof (struct node));
	root->value = values[0];
	int count;
	for (count = 1; count < num_nodes; count++){
		insert_tree (root, values[count]);
	}
	return root;
}

void create_children (int height, struct node *node, int maxHeight){
	if (height < maxHeight){
		srand(time(NULL));
		node->left = (struct node *) ssd_oalloc (1, sizeof (struct node));
		node->left->value = 2*(node->value);
		node->right = (struct node *) ssd_oalloc (1, sizeof (struct node));
		node->right->value = 2*(node->value) + 1;
		create_children (height+1, node->left, maxHeight);
		create_children (height+1, node->right, maxHeight);
	}
}

void print_tree_in_order (struct node *node){
	if (node != NULL){
		printf("%d\t", node->value);
		print_tree_in_order (node->left);
		print_tree_in_order (node->right);
	}
}

void print_tree_pre_order (struct node *node){
	if (node != NULL){
		print_tree_pre_order (node->left);
		printf("%d\t", node->value);
		print_tree_pre_order (node->right);
	}
}

bool search_tree (int value, struct node*node){
	if (node == null){
		return false;
	}
	if (node-> value == value)
		return true;

	if (node->value < value){
		return (search_tree (value, node->left));
	} else {
		return (search_tree(value, node->right));
	}
}

void update_tree (struct node*node, int old_value, int new_value){
if (node != null){
	if (node->value == old_value){
		node->value = new_value;
	} else {
		if (node->value > old_value){
			update_tree (node->left, old_value, new_value);
		} else {
			update_tree (node->right, old_value, new_value);
		}
	}
}
}

struct node *create_node (int value){
	struct node *new_node = (struct node *) ssd_oalloc (1, sizeof (struct node));
	new_node->value = value;
	return new_node;
}

void insert_tree (struct node*node, int value){
	if (node != null){
		if (node->value > value){
			if (node->left == null){
				node->left = create_node (value);
			} else {
				insert_tree (node->left, value);
			}
		} else {
			if (node->value < value){
				if (node->right == null){
					node->right = create_node (value);
				} else {
					insert_tree (node->right, value);
				}
			}
		}
	}
}
