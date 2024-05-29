#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int majorityElement(int a[], int size)
{
    int count = 0, element = -1;
    for (int i = 0; i < size; i++)
    {
        if (count == 0)
        {
            element = a[i];
            count = 1;
        }
        else if (element != a[i])
        {
            count--;
        }
        else if (element == a[i])
        {
            count++;
        }
    }
    printf("Element = %d\n", element);
    return element;
}

int main()
{
    int arr[] = {1, 2, 3, 4};
    majorityElement(arr, 4);
}