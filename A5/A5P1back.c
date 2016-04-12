#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


static unsigned char our_memory[1024 * 1024]; //reserves 1 MB for malloc
static size_t next_index = 0;

void *malloc(size_t sz)
{
    void *mem;

    if(sizeof our_memory - next_index < sz)
        return NULL;

    mem = &our_memory[next_index];
    next_index += sz;
    return mem;
}

void free(void *mem)
{
 //allows the memory that was allocated to be changed 
}