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

void check_materialize_dematerialize_code (void){
  // Create an object 
  struct node *abc = (struct node *) (ssd_oalloc (1, 4));
  // Assign some value  
  abc->value = 2;
  // Dematerialize Object
  void *page_header = object_va_to_page_header ((void *) abc);
  evict_page (page_header);
  // Access it again 
  assert (abc->value == 2);
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
	return 0;
}
