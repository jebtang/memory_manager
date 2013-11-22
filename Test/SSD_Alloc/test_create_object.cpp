#include <iostream>
#include "../../ssd_alloc.h"
#include "assert.h"
using namespace std;

void initialize_ssd_alloc (void){
	init_ssd_alloc ();
	printf ("Passed Initialization Test\n");
}

void create_object (void){
	ssd_oalloc (1, 4);
	printf ("Passed Object Creation Test\n");
}

struct node {
	int value;
};

struct list_node {
  struct list_node* next;
  int value;
};

void create_list_test (){
  int count;
  struct list_node *list_node_ptr, *root;
  root = (struct list_node *) ssd_oalloc (1, sizeof (struct list_node));
  printf ("Object Location 0x%lx\n", root);
  root->value = 0;
  list_node_ptr = root;
  for (count = 1; count < 10; count++){
    list_node_ptr->next = (struct list_node *) ssd_oalloc (1, sizeof (struct list_node)); 
    printf ("Object Location 0x%lx\n", list_node_ptr->next);
    list_node_ptr = list_node_ptr->next;
  }
  list_node_ptr = root;
  for (count = 0; count < 10; count++){
    printf ("count : %d\n", count);
    printf ("list node prt value %d\n", list_node_ptr->value);
    fflush (stdout);
    assert (list_node_ptr->value == count);
    list_node_ptr = list_node_ptr->next;
  }
}

void check_materialize_dematerialize_code (void){
  // Create an object 
  struct node *abc = (struct node *) (ssd_oalloc (1, 4));
  // Assign some value  
  abc->value = 4;
  printf ("value = %d\n", abc->value);
  // Dematerialize Object
  void *page_header = object_va_to_page_header ((void *) abc);
  evict_page (page_header);
  // Access it again 
  printf ("value = %d\n", abc->value);
  assert (abc->value == 4);
  printf ("Materialization Works");

}

void update_object (){
	struct node *abc = (struct node *) (ssd_oalloc (1, 4));
	abc->value = 2;
	assert (abc->value == 2);
	printf ("Update Object Passed\n");
}

int main (){
	initialize_ssd_alloc ();
	create_object ();
	update_object ();
	check_materialize_dematerialize_code ();
	create_list_test();
	return 0;
}
