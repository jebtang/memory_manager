/*
 * b-tree.h
 *
 *  Created on: Nov 16, 2013
 *      Author: ravitandon
 */

#ifndef B_TREE_H_
#define B_TREE_H_

#include "stdio.h"
#include "math.h"
#include <time.h>
#include <stdlib.h>
#include "stdbool.h"
#define null NULL


struct node {
	struct node * left;
	struct node * right;
	int value;
};

void init();
void finish();
struct node *create_tree (int num_nodes, int branching_factor, int *values);
void create_children (int height, struct node *node, int maxHeight);
void print_tree_in_order (struct node *node);
void print_tree_pre_order (struct node *node);
bool search_tree (int value, struct node*node);
void update_tree (struct node*node, int old_value, int new_value);
void insert_tree (struct node*node, int value);
struct node *create_node (int value);
void insert_tree (struct node*node, int value);

#endif /* B_TREE_H_ */
