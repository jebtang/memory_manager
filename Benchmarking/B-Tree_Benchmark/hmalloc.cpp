#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

// Implementation of malloc, which assigns a header to each of the objects 
void *h_malloc (std::size_t size_object){
  cout << "here" << endl;
  int *object_header = (int *) malloc (sizeof (int)); // Assigning each object with a header                                                                
  *object_header=0; // Initializing the value of the object header                                                                                           
  void *object = malloc (size_object); // Allocating an object of the requested size
  return object; // Returns the object
}

void h_free (void *object){
  int *header = (int *)(((int *)object)-1);
  free (header);
  free (object);
}

