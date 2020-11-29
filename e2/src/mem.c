#include <stdlib.h>

int memory_leaks = 0;

void* malloc_rc(size_t sz)
{
    memory_leaks++;
    return malloc(sz);
}

void free_rc(void* p)
{
    memory_leaks--;
    free(p);
}
