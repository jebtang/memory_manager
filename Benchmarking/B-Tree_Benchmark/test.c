#include <stdio.h>
#include "b-tree.h"
#include "time.h"

int main (){
	int count, array_size = 1024;
	int array[array_size];
	srand(time(NULL));
	for (count = 0; count < array_size; count++){
		array[count] = rand() % 1000;
	}
	print_tree_pre_order(create_tree (array_size, 2, array));
	return 0;
}
