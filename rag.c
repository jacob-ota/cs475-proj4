#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NLOCK 10
#define NPROC 20
int matrixDimension = NLOCK + NPROC;
int **adjacencyMatrix;
int first;
int last;
char tmpCmdType;
int *visited;

void rag_init()
{
    adjacencyMatrix = (int **)malloc(matrixDimension * sizeof(int *));
    for (int i = 0; i < matrixDimension; i++)
    {
        adjacencyMatrix[i] = (int *)malloc(matrixDimension * sizeof(int));
    }
    
}

void rag_request(int pid, int lockid)
{
    printf("PID = %d requests LOCK = %d\n", pid, lockid);
    int tmPid = pid + NLOCK;
    adjacencyMatrix[tmPid][lockid] = 1;
}

void rag_alloc(int pid, int lockid)
{
    printf("PID = %d acquires LOCK = %d\n", pid, lockid);
    adjacencyMatrix[lockid][pid + NLOCK] = 1;
    adjacencyMatrix[pid + NLOCK][lockid] = 0;
}

void dealloc(int pid, int lockid)
{
    printf("PID = %d releases LOCK = %d\n", pid, lockid);
    // checks for a allocation edge
    if (adjacencyMatrix[lockid][pid + NLOCK] == 1)
    {
        adjacencyMatrix[lockid][pid + NLOCK] = 0;
    }
    // checks for a request edge
    else if (adjacencyMatrix[pid + NLOCK][lockid] == 1)
    {
        adjacencyMatrix[pid + NLOCK][lockid] = 0;
    }
}

void rag_print()
{
    for (int i = 0; i < matrixDimension; i++)
    {
        if (i < NLOCK)
        {
            printf("L%d ", i);
        }
        else
        {
            printf("P%d ", i - NLOCK);
        }
        for (int j = 0; j < matrixDimension; j++)
        {
            printf("%d ", adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}
void init_DFS()
{
    visited = (int *)malloc(NLOCK * sizeof(int));
}
void deadlock_detect(int pid, int lockid)
{
    // First 10 Locks & Last 20 Pids (pid + NLOCK)
    // Tracks visited nodes
    visited[lockid] = 1;
}

int main(int argc, char *argv[])
{
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Please provide valid file");
        exit(0);
    }
    rag_init();
    while (1)
    {
        if (feof(file))
        {
            break;
        }

        fscanf(file, "%d", &first);
        fscanf(file, "%s", &tmpCmdType);
        fscanf(file, "%d", &last);
        if (!strcmp(&tmpCmdType, "R"))
        {
            rag_request(first, last);
        }
        else if (!strcmp(&tmpCmdType, "A"))
        {
            rag_alloc(first, last);
        }
        else if (!strcmp(&tmpCmdType, "D"))
        {
            dealloc(first, last);
        }
    }
    return 0;
}