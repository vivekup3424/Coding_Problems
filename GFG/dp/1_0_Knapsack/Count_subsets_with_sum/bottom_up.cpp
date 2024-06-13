#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
//#define MAX 100
// int t[MAX][MAX];

// Count of subsets sum with a Given sum
// Given an array arr[] of length N and an integer X,
// the task is to find the number of subsets with sum equal to X.
int count_subsets(int arr[], int n, int sum)
{
    int t[n + 1][sum + 1];              // t[0 1...n][0 1...sum]
    memset(t, -1, (n + 1) * (sum + 1)); // inputing -1 in all places of the matrix;
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < sum + 1; j++)
        {
            if (j == 0)
            {
                t[i][j] = 1;
            } // for sum = 0, there would be only as there are only positive numbers here
            else if (i == 0)
            {
                t[i][j] = 0;
            } // if n=0, there are no subsets for sum>0
            else
            {
                if (arr[i - 1] <= j) // ith element<= sum
                {
                    t[i][j] = t[i - 1][j - arr[i - 1]] + t[i - 1][j]; // lookup rule
                }
                else // ith element>sum, hence not includint it in the subset
                {
                    t[i][j] = t[i - 1][j];
                }
            }
        }
    }
    return t[n][sum]; // outputting the total number of subsets
    // Time: O(n^2) & Space: O(n^2)
}
int main()
{
    int length = 0, sum = 0;
    std::cout << "Enter the length of the array: ";
    cin >> length;
    int array[length];
    cout << "Enter the values in the array: \n";
    for (int i = 0; i < length; i++)
    {
        cin >> array[i];
    }
    cout << "Enter the sum: ";
    cin >> sum;
    int total = count_subsets(array, length, sum);
    cout << "Total number of subsets " << total << ".\n";
    return 0;
}