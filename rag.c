#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NLOCK 5
#define NPROC 10
int matrixDimension = NLOCK + NPROC;
int **adjacencyMatrix;
int first;
int last;
char tmpCmdType;
int *visited;
int deadlocks[NLOCK + NPROC];
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
int dfs(int deadIndx, int vertex, int *visited)
{
    // Vertex = Current Testing Lock
    visited[vertex] = 1;
    // int deadIndex = 0;
    for (int currHorizPid = 0; currHorizPid < matrixDimension; currHorizPid++) // i = col (pid)
    {
        // printf("Vertex %d & i = %d\n", vertex, currHorizPid);
        if (adjacencyMatrix[vertex][currHorizPid])
        {
            for (int row = NLOCK; row < matrixDimension; row++) // Go through col of Lock vertex
            {
                if (adjacencyMatrix[row][vertex] == 1 && row != currHorizPid) // If detecting a 1 other than currHorizPid
                {
                    // printf("Deadlock detected, Lock %d acquired by pid %d but requested by pid %d \n", vertex, currHorizPid - NLOCK, row - NLOCK);
                    // Duplicate pid=2 lockid=1 for input_file4, otherwise works perfectly
                    deadlocks[deadIndx] = currHorizPid - NLOCK; // PID THAT IS DEADLOCKING
                    deadIndx++;
                    deadlocks[deadIndx] = vertex;
                    deadIndx++;
                }
            }
        }
    }
    if (vertex < NLOCK - 1)
    {
        deadIndx = dfs(deadIndx, vertex + 1, visited);
    }

    return deadIndx;
}
int deadlock_detect()
{
    int visited[matrixDimension];
    for (int i = 0; i < matrixDimension; i++)
    {
        visited[i] = 0;
    }
    return dfs(0, 0, visited);
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
    int deadIndex = deadlock_detect();
    for (int i = 0; i < deadIndex; i++)
    {
        if (i == 0 || i % 2 == 0)
        {
            printf("pid=%d ", deadlocks[i]);
        }
        else
        {
            printf("lockid=%d \n", deadlocks[i]);
        }
        // printf("\n\npid=%d lockid=%d\n", deadlocks[i], deadlocks[i + 1]);
    }

    rag_print();
    return 0;
}