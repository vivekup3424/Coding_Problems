#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>

struct semaphore{
    Queue<process> q;
    int value;
};
