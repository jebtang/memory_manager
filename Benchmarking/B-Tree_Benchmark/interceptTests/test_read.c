#include <stdio.h>
#include "b-tree.h"
#include "time.h"
//#include <iostream>
//#include "../../ssd_alloc.h"
#include <sys/time.h>
#include <unistd.h>

//using namespace std;

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
	int num_iterations = 10;
	long sum_time = 0, ave_time, max_time = 0, min_time;
	int current_iteration = 0;
	while (current_iteration < num_iterations){
	for (count = 0; count < read_array_size; count++){
	  read_array [count] = rand();
	}
        gettimeofday(&start, NULL);
	
	for (count = 0; count < read_array_size; count++){
	  search_tree (array[count % array_size], root);// read_array[count]);
	}
	gettimeofday(&end, NULL);
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds) * 1000 + useconds/1000.0);
	if (current_iteration == 0){
	  min_time = mtime;
	}
	if (mtime > max_time){
	  max_time = mtime;
	}
	if (mtime < min_time){
	  min_time = mtime;
	}
	sum_time = sum_time + mtime;
	current_iteration++;
	}
	ave_time = sum_time / num_iterations;
	printf("%ld,%ld,%ld\n", ave_time, min_time, max_time);
	return 0;
}
