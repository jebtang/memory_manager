#include <iostream>
#include <unordered_map>
#include "memory_monitor.h"
using namespace std;
unordered_map <void *, int> memory_map;
unordered_map <void *, int> :: iterator it;

void print_memory(){
  for (it = memory_map.begin(); it != memory_map.end(); it++){
    cout << "memory location = " << it->first << ": access count" << it->second << endl;
  }
}
 void access(void *memory_location, int count){
   int *x = ((int *)memory_location-1);
   (*x)++;
   return;
    int new_value;
    it = memory_map.find (memory_location);
    if (it == memory_map.end())
      new_value=count;
    else {
      new_value = it->second + count;
      memory_map.erase (it);
    }
    memory_map.insert(pair <void *, int> (memory_location, new_value));
  }

  void define(void * memory_location){
    memory_map.insert (pair <void *, int> (memory_location, 1));
    return;
}
