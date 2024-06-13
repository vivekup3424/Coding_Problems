/*Bubble Sort is the simplest sorting algorithm that 
works by repeatedly swapping the adjacent elements 
if they are in the wrong order. This algorithm is 
not suitable for large data sets as its average and 
worst-case time complexity is quite high.*/

#include <stdio.h>
using namespace std;

void swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[],int N) //N is length of the array
{
    int i,j; //loop counters
    for ( i = 0; i < N; i++)
    {
        for ( j = 0; j < N-1-i; j++) //last i elements are aleady in order
        {
            if(arr[j]>arr[j+1])
            {
                swap(arr+j,arr+j+1);
            }
        }
    }
}

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
 
// Driver program to test above functions
int main()
{
    int arr[] = { 64, 34, 25, 12, 22, 11, 90 };
    int n = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, n);
    printf("Sorted array: \n");
    printArray(arr, n);
    return 0;
}