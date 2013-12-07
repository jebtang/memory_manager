#include "stdio.h"
#include "stdlib.h"
struct node {
  int value;
  struct node *next;
};

void construct_tree (struct node *root, int number_nodes){
  int count = 1;
  struct node* current_node = root;
  while (count < number_nodes){
    current_node->next = (struct node *) malloc (sizeof(struct node));
    current_node->next->value = ++count;
    current_node = current_node->next;
  }
   
   current_node->next = NULL;
}

void traverse_tree (struct node *root){
  int count = 0, num_nodes = 0;
  struct node *current_node = root;
  while (current_node != NULL){
     num_nodes++;
    current_node = current_node->next;
  }
  printf("Number of nodes %d\n", num_nodes);
}

int main(){
  struct node *root = (struct node *) malloc (sizeof(struct node));
  root->value = 1;
  construct_tree (root, 100000);
  traverse_tree (root);
  return 0;
}

