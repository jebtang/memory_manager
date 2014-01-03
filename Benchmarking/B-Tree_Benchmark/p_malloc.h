#ifndef _P_MALLOC_
#define _P_MALLOC_

#include <iostream>
#include "stdio.h"
#include "stdlib.h"


//using namespace std;

void *p_malloc(std::size_t size);
void p_free (void *object);

#endif
