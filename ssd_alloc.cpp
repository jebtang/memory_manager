#include <time.h>       /* time */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include <signal.h>
#include "ssd_alloc.h"
using namespace std;

#define handle_error(msg) \
  do {perror (msg); exit(EXIT_FAILURE);} while (0)
#define PAGE_BUFFER_SIZE 10 // The page buffer has 10 pages in memory 
int PAGE_SIZE =  sysconf(_SC_PAGE_SIZE); // Each page in page buffer is of size 4KB

void *page_buffer; // This is the base location of the page buffer, location in memory where all the pages are materialized

bool page_buffer_bitmap[PAGE_BUFFER_SIZE]; // Have to convert it to bitmap
struct sigaction sa;

map <void*, struct object> object_table; // This is the object table which stores the exact location of objects to fetch them
std::map<void *, struct object>::iterator object_table_it; // Iterator of the map

// This function updates the object table with a given object header
void insert_object (struct page_header *ph, void *page_address){
  // Build the object from the page header 
  struct object ob = get_object_from_header (ph, page_address);
  // Insert the object into the object table 
  object_table.insert (pair <void *, struct object> (ph->object_va, ob));
}

// This function gets an object from a page header
struct object get_object_from_header (struct page_header *ph, void *page_address){
  struct object ob;
  void *start_object = (void *)((struct page_header *) page_address + 1);
  ob.size = ph->object_size;
  ob.value = malloc (sizeof (ph->object_size));
  memcpy (ob.value, start_object, ph->object_size);
  return ob;
}


// The handler to catch SIGSEGV faults on memory access 
void seg_handler(int sig, siginfo_t *si, void *unused){
  printf("Got SIGSEGV at address: 0x%lx\n", (long) si->si_addr);
  printf("Signal Code %d", si->si_code);
  // Calling the materialize page function 
  if (si->si_code == SEGV_ACCERR){
    materialize_page (si->si_addr);   // materializing the page from the object table 
    mprotect (si->si_addr, PAGE_SIZE, PROT_READ | PROT_WRITE); // after page materialization the protection levels of the page are changed 
  }
  else
    handle_error ("Segmentation fault");
}

void init_ssd_alloc (void){
   // Initializing the page buffer to get memory space from for storing the pages in the page buffer 
  int value = posix_memalign (&page_buffer, PAGE_SIZE, PAGE_BUFFER_SIZE * PAGE_SIZE);
  if (value == EINVAL) 
    handle_error("aligment has to be a power of 2");
  if (value == ENOMEM) 
    handle_error("out of memory");
  // defining the seg fault handler 
  sa.sa_flags = SA_SIGINFO; // The siginfo_t structure is passed as a second parameter to the user signal handler function
  sigemptyset(&sa.sa_mask); // Emptying the signal set associated with the structure sigaction_t 
  sa.sa_sigaction = seg_handler; // Assigning the fault handler 
  if (sigaction(SIGSEGV, &sa, NULL) == -1) // Installs the function in sa taken on a segmentation fault
    handle_error("sigaction");

}

struct object init_object(int size){
  struct object ob;
  ob.value = malloc (size); // the object is initialized
  ob.size = size; // storing the size of the object
  return ob;
}

void *ssd_oalloc (int num_objects, int size_object){
  // Insert the object in object table
  // Allocating page in memory to the object, currently we implement it for objects of size < 4KB and num_objects = 1 
  void *object_location = malloc (PAGE_SIZE); // object_location is the virtual memory address of the object 
  object_table.insert(pair <void *, struct object> (object_location, init_object (size_object))); // On an initialization, some memory is allocated to the object and is pushed into memory
  // Protecting the page so that on each access the page faults, protection mechanism is for any access 
  if (mprotect (object_location, PAGE_SIZE, PROT_NONE) == -1){
    handle_error("mprotect");
  }
  return object_location;
}

int select_random_page (void){
  /* initialize random seed: */
  srand (time(NULL));
  /* returns a random page from the page buffer: */
  return (rand() % PAGE_BUFFER_SIZE);
}

// Function which gets a free page from the page buffer 
void *get_free_page (void){
  int count; void *page_address;
  for (count = 0; count < PAGE_BUFFER_SIZE; count++){
    if (!(page_buffer_bitmap[count])){
      break;
    }
  }
  // Checking if a free page has been found within the page buffer 
  if (count < PAGE_BUFFER_SIZE){
    return (void *)((char *) page_buffer + count * PAGE_SIZE);
  } else {
    printf ("page buffer is filled, evicting a page");
    // Page eviction is not done as yet, hence evicting the current page 
    /* initialize random seed: */
    
    void *victim_page_address = (void *)((char *)page_buffer + select_random_page() * PAGE_SIZE); 
    evict_page (victim_page_address);
    return victim_page_address;
  }
}

/* This function evicts a victim page from the page buffer: */
void evict_page (void *victim_page_address){
  // Store the page back to the page table
  // We would need the size of the object on the page also 
  struct page_header *ph = (struct page_header *) malloc (sizeof (struct page_header));
  // Copying the header from the page to get object's size
  memcpy (ph, victim_page_address, sizeof(page_header));
  int object_size = ph->object_size;
  // Saving the object back to the object table
  insert_object (ph, victim_page_address);  
}

// The page materialization function gets an argument as the address of the object and returns the address of the page 
void materialize_page (void *va){
  // Getting a free page from the page buffer
  void *free_page = get_free_page ();
  // Getting the object our from the object table
  object_table_it = object_table.find (va);
  // Checking if no free page is found 
  if (object_table_it == object_table.end()){
    printf ("Object with address 0x%lx not found in the object table \n", (long)va);
    exit (EXIT_FAILURE);
  }
  // Getting the object out
  struct object ob = object_table_it->second; 
  // Constructing the page header 
  struct page_header *ph = (struct page_header *) malloc (sizeof(struct page_header)); // has to be freed later on 
  ph->object_size = ob.size; // assiging the object size to the page header
  ph->object_va = va; // assigning the virtual address to the page header
  memcpy(free_page, ph, sizeof (struct page_header)); // copying the page header to the page in the page buffer 
  free (ph); // the page header is freed here
  memcpy((void *)((struct page_header*)free_page + 1), ob.value, ob.size); // copying the object to the materialized page 
  // the memory allocated by to store the object in the object table is freed because on materializing an object the page has to be removed from the object table 
  free (ob.value); // this prevents memory leakage 
}


int main (){
  return 0;
}
