#ifndef _SSD_ALLOC_H_
#define _SSD_ALLOC_H_
#include <iostream>
using namespace std;

void *ssd_oalloc (int num_objects, int size_objects);
void ssd_free (void *va_address);

#endif
