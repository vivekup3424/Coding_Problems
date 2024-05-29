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
    printf("Count=  %d\n", count);
    return element;
}

int main()
{
    int arr[] =
        {
            17,
            19,
            9,
            5,
            3,
            6,
            17,
            7,
            18,
            16,
            18,
            11,
            3,
            15,
            2,
        };
    majorityElement(arr, 15);
}