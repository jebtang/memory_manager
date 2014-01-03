

#include "memory_monitor.h"

/*void print_memory(){
  for (it = memory_map.begin(); it != memory_map.end(); it++){
    cout << "memory location = " << it->first << ": access count" << it->second << endl;
  }
  }*/
 void access(void *memory_location, int count){
   int *x = ((int *)memory_location-1);
   (*x)++;
   return;
}

/*  void define(void * memory_location){
    memory_map.insert (pair <void *, int> (memory_location, 1));
    return;
    }*/
