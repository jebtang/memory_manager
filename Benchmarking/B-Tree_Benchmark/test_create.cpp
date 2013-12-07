#include <stdio.h>
#include "b-tree.h"
#include "time.h"
#include <iostream>
#include "../../ssd_alloc.h"
#include <sys/time.h>
#include <unistd.h>

using namespace std;

int main (){  
        struct timeval start, end;
        gettimeofday(&start, NULL);
        long mtime, seconds, useconds;  
        init ();
	int count, array_size = 1000*25;
	int array[array_size];
	srand(time(NULL));
	for (count = 0; count < array_size; count++){
	  array[count] = rand();
	}
	struct node *root = create_tree (array_size, 2, array);
	//	print_tree_pre_order (root);
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	printf("Elapsed time: %ld milliseconds\n", mtime);
	//	finish ();
	return 0;
}
