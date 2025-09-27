#include <stdio.h>
#include <stdlib.h>

typedef struct KStacks
{
    int *arr;
    int *top;
    int *next;
    int freeTop;
    int n;
} KStacks;

KStacks *createKStacks(int n, int k)
{
    KStacks *kStacks = (KStacks *)(malloc(sizeof(KStacks)));
    if (kStacks == NULL)
    {
        return NULL;
    }
    kStacks->arr = (int *)(malloc(sizeof(int) * n));
    kStacks->top = (int *)(malloc(sizeof(int) * k));
    kStacks->next = (int *)(malloc(sizeof(int) * n));
    if (!kStacks->arr || !kStacks->top || !kStacks->next)
    {
        free(kStacks->arr);
        free(kStacks->top);
        free(kStacks->next);
        free(kStacks);
        return NULL;
    }
    kStacks->n = n;
    kStacks->freeTop = 0;
    for(int i = 0; i < k; i++){
        kStacks->top[i]=-1;
    }
    for(int i = 0; i )
    return kStacks;
}

void push(KStacks *kstacks, int stackIdx, int element)
{
    kstacks->next[kstacks->freeTop] = kstacks->top[stackIdx];
    kstacks->arr[kstacks->freeTop] = element;
    kstacks->top[stackIdx] = kstacks->freeTop;
    kstacks->freeTop++;
}

int pop(KStacks *kstacks, int stackIdx)
{
    if (kstacks->top[stackIdx] == -1)
    {
        return -1;
    }
    int value = kstacks->arr[kstacks->top[stackIdx]];
}