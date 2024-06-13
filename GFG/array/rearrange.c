#include <stdio.h>
/*Given an array of elements of length N, ranging from 0 to N – 1.
All elements may not be present in the array. If the element
is not present then there will be -1 present in the array.
Rearrange the array such that A[i] = i and if i is not present,
display -1 at that place.*/

/*Input : arr = {-1, -1, 6, 1, 9, 3, 2, -1, 4, -1}
Output : [-1, 1, 2, 3, 4, -1, 6, -1, -1, 9]

Input : arr = {19, 7, 0, 3, 18, 15, 12, 6, 1, 8,
              11, 10, 9, 5, 13, 16, 2, 14, 17, 4}
Output : [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 
         11, 12, 13, 14, 15, 16, 17, 18, 19]*/

/*Approach(Naive Approach):

    Nav­i­gate the numbers from 0 to n-1.
    Now navigate through array.
    If (i==a[j]) , then replace the element at i position with a[j] position.
    If there is any element in which -1 is used instead of the number then it will be replaced automatically.
    Now, iterate through the array and check if (a[i]!=i) , if it s true then replace a[i] with -1.*/
// C program for above approach


/******#include <stdio.h>

// Function to transform the array
void fixArray(int ar[], int n)
{
	int i, j, temp;

	// Iterate over the array
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			// Check is any ar[j]
			// exists such that
			// ar[j] is equal to i
			if (ar[j] == i) {
				temp = ar[j];
				ar[j] = ar[i];
				ar[i] = temp;
				break;
			}
		}
	}

	// Iterate over array
	for (i = 0; i < n; i++)
	{
		// If not present
		if (ar[i] != i)
		{
			ar[i] = -1;
		}
	}

	// Print the output
	printf("Array after Rearranging\n");
	for (i = 0; i < n; i++) {
		printf("%d ",ar[i]);
	}
}

// Driver Code
int main()
{
	int n, ar[] = { -1, -1, 6, 1, 9, 3, 2, -1, 4, -1 };
	n = sizeof(ar) / sizeof(ar[0]);

	// Function Call
	fixArray(ar, n);
}
********/

/*Another Approach (Swap elements in Array) : 
1) Iterate through elements in an array 
2) If arr[i] >= 0 && arr[i] != i, put arr[i] at i ( swap arr[i] with arr[arr[i]])*/

void swap(int *a,int *b)
{
    int *c = b;
    b = a;
    b = c;
    return ;
}
void rearrange_array(int arr[],int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i]>0 && arr[i]!=i)
        {
            swap(arr+i,arr+arr[i]);
        }
    }
}
void print_array(int arr[],int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ",arr[i]);        
    }
    printf("\n");
}
int main()
{
    int arr[8] = {-1,2,1,5,6,4,-1,7};
    rearrange_array(arr,8);
    printf("Rearrange array");
    print_array(arr,8);
    return 0;
}