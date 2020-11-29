#ifndef _MEM_H_
#define _MEM_H_

#include <stdlib.h>
extern int memory_leaks;

void free_rc(void* p);
void* malloc_rc(size_t sz);

#define malloc malloc_rc
#define free free_rc

#endif // _MEM_H_
