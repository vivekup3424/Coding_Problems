#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *arr = (int *)malloc(10*sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        scanf("%d",(arr+i));
    }
    printf("The array is: \n");
    for (int i = 0; i < 10; i++)
    {
        printf("%d\t",arr[i]);
    }
    printf("\n");
}