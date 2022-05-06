/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

void printchar(char c)
{
    lid32 lock = lock_create();
    int i;
    acquire(lock);
    for (i = 0; i < 10; i++)
        kprintf("%c", c);
    release(lock);
}

int main(uint32 argc, uint32 *argv)
{
    // priority of process is input as the 3rd argument of create()
    ready(create((void *)printchar, INITSTK, 15, "P1", 1, 'A'), FALSE);
    ready(create((void *)printchar, INITSTK, 15, "P2", 1, 'B'), FALSE);

    return 0;
}
