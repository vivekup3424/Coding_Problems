// move all negative numbers to begining and positive to end
// with constant space

// I am going to use two pointer approach with low and high pointer

#include <bits/stdc++.h>
using namespace std;
bool isNegative(int neg)
{
    if (neg < 0)
        return true;
    else
        return false;
}
void seperate(vector<int> &arr, int length)
{
    int low = 0;
    int high = length - 1;
    while (low <= high)
    {
        if (isNegative(arr[low]))
            low++;
        else
        {
            swap(arr[low], arr[high]);
            high--;
        }
    }
    return;
}
void printVector(vector<int> &arr, int length)
{
    for (auto i = 0; i < length; i++)
    {
        cout << arr[i] << ", ";
    }
    cout << endl;
    return;
}
// Time Complexity = O(n)
// Space Complexity = O(1)
int main()
{
    vector<int> arr = {-12, 11, -13, -5, -3, -6, 19};
    seperate(arr, arr.size());
    printVector(arr, arr.size());
    return 0;
}