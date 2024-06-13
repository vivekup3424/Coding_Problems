//The selection sort algorithm sorts an array by repeatedly 
//finding the minimum element (considering ascending order) 
//from the unsorted part and putting it at the beginning.

//The algorithm maintains two subarrays in a given array.
//
//    The subarray which already sorted. 
//    The remaining subarray was unsorted.

//Follow the below steps to solve the problem:
//
//    Initialize minimum value(min_idx) to location 0.
//    Traverse the array to find the minimum element in the array.
//    While traversing if any element smaller than min_idx is found then swap both the values.
//    Then, increment min_idx to point to the next element.
//    Repeat until the array is sorted.

// C++ program for implementation of selection sort
#include <bits/stdc++.h>
using namespace std;

void swap(int *a,int *b)
{
	int *temp;
	*temp = *a;
	*a = *b;
	*b = *temp;
}

void selectionSort(int arr[],int length)
{
	int min_index;
	// One by one move boundary of unsorted subarray
	for (int i = 0; i < length-1; i++)
	{
		min_index = i;
		for (int j = i+1; i < length; j++)
		{
			if(arr[j]<arr[min_index])
			{
				min_index = j;
			}
		}
		// Swap the found minimum element with the first element
		swap(arr+min_index,arr+i);
		
	}
	
}
/*void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
		if (arr[j] < arr[min_idx])
			min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
	}
}*/

/* Function to print an array */
void printArray(int arr[], int size)
{
	int i;
	for (i=0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

// Driver program to test above functions
int main()
{
	int arr[] = {64, 25, 12, 22, 11};
	int n = sizeof(arr)/sizeof(arr[0]);
	selectionSort(arr, n);
	cout << "Sorted array: \n";
	printArray(arr, n);
	return 0;
}

/*Time Complexity: The time complexity of Selection Sort is O(N2) as 
there are two nested loops:

    One loop to select an element of Array one by one = O(N)
    Another loop to compare that element with every other Array element = O(N)

Therefore overall complexity = O(N) * O(N) = O(N*N) = O(N2)

Auxiliary Space: O(1) as the only extra memory used is for 
temporary variables while swapping two values in Array. 
The selection sort never makes more than O(N) swaps and 
can be useful when memory write is a costly operation.*/
