#include "memory_monitor.h"
#include "stdio.h"
#include "stdlib.h"
struct node {
  int value;
  struct node *next;
};
void construct_tree (struct node *root, int number_nodes){
  int count = 1;
  struct node* current_node = root;
access ((void *)current_node ,1);
  while (count < number_nodes){
    current_node->next = (struct node *) malloc (sizeof(struct node));
access ((void *)current_node ,1);
    current_node->next->value = ++count;
access ((void *)current_node ,1);
access ((void *)current_node->next ,1);
    current_node = current_node->next;
access ((void *)current_node ,1);
access ((void *)current_node ,1);
  }
}

void traverse_tree (struct node *root){
  int count = 0, num_nodes = 0;
  struct node *current_node = root;
access ((void *)current_node ,1);
  while (current_node != NULL){
access ((void *)current_node ,1);
     num_nodes++;
    current_node = current_node->next;
access ((void *)current_node ,1);
access ((void *)current_node ,1);
  }
  printf("Number of nodes %d\n", num_nodes);
}

int main(){
  struct node *root = (struct node *) malloc (sizeof(struct node));
access ((void *)root ,1);
  root->value = 1;
access ((void *)root ,1);
  construct_tree (root, 100);
access ((void *)root ,1);
  traverse_tree (root);
access ((void *)root ,1);
  return 0;
}

