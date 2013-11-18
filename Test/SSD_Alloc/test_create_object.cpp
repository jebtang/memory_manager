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
