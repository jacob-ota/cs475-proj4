#include <stdio.h>
#include <stdlib.h>

#define NLOCK = 10
#define NPROC = 20
int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Please provide valid file");
        exit(0);
    }
}

void rag_init()
{
}

void rag_request(int pid, int lockid)
{
}

void rag_alloc(int pid, int lockid)
{
}

void dealloc()
{
}
