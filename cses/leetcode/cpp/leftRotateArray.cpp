
#include <bits/stdc++.h>
using namespace std;
void leftRotateOnePlace(vector<int> v)
{
    int n = v.size();
    int temp = v[0];
    for (int i = 1; i < n; i++)
    {
        v[i - 1] = v[i];
    }
    v[n - 1] = temp;
    // Time Complexity = O(n)
    // Space Complexity = O(n)
    // Auxilliary Space = O(1) //extra space
}

// left rotations by D places

// Method 1:- Left rotate the array by one place for D iterations
void leftRotate1(vector<int> v, int D)
{
    for (int i = 0; i < D; i++)
    {
        leftRotateOnePlace(v);
    }
    // Time Complexity = O(D*n) = O(n^2)
}

// Method 2:- Using a temp array for first D items, and then using shifting to leftplace for other n-D items
void leftRotate2(vector<int> v, int D)
{
    vector<int> temp(D);
    int i = 0;
    int n = v.size();
    for (; i < D; i++)
    {
        temp[i] = v[i];
    }
    // now i =D
    for (; i < n; i++)
    {
        v[i - D] = v[i];
    }
    // put back temp in the array
    for (i = 0; i < D; i++)
    {
        v[n - D + i + 1] = temp[i]; // occupying the last D places
    }
    // Time complexity = O(n+d)
    // Space Complexity = O(D) + O(n-D)+O(D) , auxilliary space = O(D) used for saving the temp array.
}

// improvement over leftRotate2 by using only the constant extra space, and not storing any linear data structure

// I could have thought of solution involving mod by then again I would have to use linear temp vector

// here the optimal algo:-
// 1.reverse v from v to v+d-1, and then reverse(v+d, v.end()), and then reverse(v.begin(), v.end())

// similar thing can be done for right rotation as in leetcode, in that I reverse the right part and left part 189
void leftRotate3(vector<int> v, int D)
{
    // left rotate the vector v by D indices
}
int main()
{
}