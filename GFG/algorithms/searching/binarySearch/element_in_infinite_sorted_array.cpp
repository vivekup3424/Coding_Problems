/*
https://www.geeksforgeeks.org/find-position-element-sorted-array-infinite-numbers/

Required Solution

int low = 0
int high = 1
while(key>arr[high])
{
    low = high;
    high = high*2
}
*/