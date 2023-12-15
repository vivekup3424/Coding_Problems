#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXQUEUE 100
struct queue
{
    int items[MAXQUEUE];
    int front;
    int rear;
};

int main()
{
    struct queue q;
    q.front = q.rear=MAXQUEUE-1;

    return 0;
}