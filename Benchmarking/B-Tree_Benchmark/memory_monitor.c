

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

int getAccessCount (void *object_address){
  int *header_address = (int *)((int *) object_address - 1);
  int count = *header_address;
  return count;
}
