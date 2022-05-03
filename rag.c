#define NLOCK 10
#define NPROC 20
#include <stdlib.h>
int **adjacencyMatrix;

void rag_init()
{
    adjacencyMatrix = (int **)malloc(NPROC * sizeof(int *));
    for(int i = 0; i < NPROC; i++) {
        adjacencyMatrix[i] = (int *)malloc(NPROC * sizeof(int));
    }
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

void rag_print() 
{
    for(int i = 0; i < NPROC; i++) {
        for(int j = 0; j < NPROC; j++) {
            printf("%d ", adjacencyMatrix[i][j]);
        }
    }
}