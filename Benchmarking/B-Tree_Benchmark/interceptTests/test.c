#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* Implementation of the header malloc function */
void *hmalloc (size_t bytes){
  printf("In H_Malloc\n");
  bytes = bytes + sizeof (int); // adding the header as an integer
  void *victim = malloc (bytes);
  memset(victim, 0, sizeof (int));
  victim = (void *)((int *)victim + 1);
  return victim;
}

/* Implementation of the free function, which frees the header */
void hfree (void *memory){
  void *header = (void *)((int *)memory -1);
  free (header);
}

void __assert(bool a){
  if (!a){
    printf("failure\n");
    exit (-1);
  }
}

int main (){
 void *abc = hmalloc (sizeof(int));
 int *count = (int *)((int *)abc -1); 
 printf ("%d\n", *count);
   __assert (*count== 0);
   (*count)++;
   int *count1 = (int *)((int *)abc-1);
   __assert(*count1 == 1);
   printf ("%d\n", *count1);
 hfree (abc);
 printf("success\n");
 return 0;
}
