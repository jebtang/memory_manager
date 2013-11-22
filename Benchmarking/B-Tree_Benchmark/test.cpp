#include <stdio.h>
#include "b-tree.h"
#include "time.h"
#include <iostream>
#include "../../ssd_alloc.h"

using namespace std;

int main (){
        init ();
	int count, array_size = 5;
	int array[array_size];
	srand(time(NULL));
	for (count = 0; count < array_size; count++){
		array[count] = rand() % 1000;
	}
	printf ("Creating the tree \n");
	struct node *root = create_tree (array_size, 2, array);
	printf ("Tree created \n");
	print_tree_pre_order (root);
	printf ("Test Passed \n");
	return 0;
}
