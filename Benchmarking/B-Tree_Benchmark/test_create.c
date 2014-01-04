#include <stdio.h>
#include "b-tree.h"
#include "time.h"
#include <sys/time.h>
#include <unistd.h>

int main (int argc, char **argv){  
        int num_iterations = 1, curr_iteration = 0;
        struct timeval start, end;
        long mtime, seconds, useconds, sum_mtime = 0;
        double avg_mtime;  
        init ();
	int count, array_size = 1000;
	if (argc > 1)
	  array_size = atoi (argv[1]);
	int array[array_size];
	srand(time(NULL));
	for (count = 0; count < array_size; count++){
	  array[count] = rand();
	}
	for (curr_iteration = 0; curr_iteration < num_iterations; curr_iteration++){
        gettimeofday(&start, NULL);
	struct node *root = create_tree (array_size, 2, array);
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	sum_mtime += mtime;
	//	destroy_tree (root);
	}
        avg_mtime = sum_mtime / num_iterations;
	printf("%lf", avg_mtime);
	return 0;
}
