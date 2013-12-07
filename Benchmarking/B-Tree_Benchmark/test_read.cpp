#include <stdio.h>
#include "b-tree.h"
#include "time.h"
#include <iostream>
#include "../../ssd_alloc.h"
#include <sys/time.h>
#include <unistd.h>

using namespace std;

int main (int argc, char **argv){  
        struct timeval start, end;
        long mtime, seconds, useconds;  
        init ();
	int count, array_size = 1000*25, read_array_size;
	int array[array_size];
	srand(time(NULL));
	for (count = 0; count < array_size; count++){
	  array[count] = rand();
	}
	struct node *root = create_tree (array_size, 2, array);
	if (argc > 1)
	  read_array_size = atoi (argv[1]);
	else 
	  read_array_size = array_size;
	int read_array[read_array_size];
	for (count = 0; count < read_array_size; count++){
	  read_array [count] = rand();
	}
        gettimeofday(&start, NULL);

	for (count = 0; count < array_size; count++){
	  search_tree (read_array[count], root);
	}
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	printf(" %ld\n", mtime);
	return 0;
}
