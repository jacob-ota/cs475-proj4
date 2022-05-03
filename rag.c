#include <stdio.h>
#include <stdlib.h>

#define NLOCK 10
#define NPROC 20
int **adjacencyMatrix;
int first;
int last;

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
    adjacencyMatrix = (int **)malloc(NPROC * sizeof(int *));
    for (int i = 0; i < NPROC; i++)
    {
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
    for (int i = 0; i < NPROC; i++)
    {
        for (int j = 0; j < NPROC; j++)
        {
            printf("%d ", adjacencyMatrix[i][j]);
        }
    }
}
