#include <stdio.h>
#include <stdlib.h>
/*Write a program to reverse an array or string*/
int arr[8] = {1,2,3,4,5,6,7,8};
void print_array(int arr[],int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);        
    }
    printf("\n");
}
/*1) Initialize start and end indexes as start = 0, end = n-1 
2) In a loop, swap arr[start] with arr[end] and change start and end as follows : 
start = start +1, end = end – 1*/
void reverse1(int arr[],int length)
{
    int start = 0,end = length-1;
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
    printf("The reverse array is: ");
    print_array(arr,length);
    return ;
}

int main()
{
    reverse1(arr,8);
    return 0;
}