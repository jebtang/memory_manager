#include <iostream>
#include <map>
#include "memory_monitor.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
map <void *, int> memory_map;
map <void *, int> :: iterator it;

void print_memory(){
  for (it = memory_map.begin(); it != memory_map.end(); it++){
    cout << "memory location = " << it->first << ": access count" << it->second << endl;
  }
}
 
 int new_value;
 void access(void *memory_location, int count){
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
