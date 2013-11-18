#ifndef _SSD_ALLOC_H_
#define _SSD_ALLOC_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include <signal.h>
//#include <sys/siginfo.h>

using namespace std;

struct object {
  void *value;
  int size;
};

/* Each page has a header. The header currently stores the size of the object on the page. */
struct page_header {
  int object_size;
};


void *ssd_oalloc (int num_objects, int size_objects);
void ssd_free (void *va_address);
void seg_handler(int sig, siginfo_t *si, void *unused);
void init_ssd_alloc (void);
struct object init_object(int size);
void materialize_page (void *va);
void evict_page(void *);
int get_free_page(void);
int select_random_page(void);
struct object init_object (int);
struct object get_object_from_header (struct page_header *ph, void *page_address);
void *page_header_to_object_va (void *ph);
void *object_va_to_page_header(void *object_va);

#endif
