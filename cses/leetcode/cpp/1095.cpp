
#include <bits/stdc++.h>
using namespace std;

// This is the MountainArray's API interface.
// You should not implement it, or speculate about its implementation
class MountainArray
{
public:
    int get(int index);
    int length();
};

class Solution
{
public:
    int getpeakIndexInMountainArray(MountainArray &mountainArray)
    {
        int n = mountainArray.length();
        int l = 0, r = n - 1;
        while (l < r)
        {
            int m = l + (r - l) / 2;
            if (mountainArray.get(m) >= mountainArray.get(m + 1))
            {
                r = m;
            }
            else
            {
                l = m + 1;
            }
        }
        return l;
    }
    int findElement(int target, MountainArray &mountainArr, int l, int r) //(2,3)
    {
        int n = mountainArr.length();
        if (l == r)
        {
            return mountainArr.get(l) == target ? l : -1;
        }
        while (l < r)
        {
            int m = (l + r) / 2;
            if (mountainArr.get(m) == target)
                return m;
            else if (mountainArr.get(m) < target)
            {
                l = m + 1;
            }
            else
            {
                r = m - 1;
            }
        }
        return -1;
    }
    int findInMountainArray(int target, MountainArray &mountainArr)
    {
        int n = mountainArr.length();                                // 4
        int indexPeak = getpeakIndexInMountainArray(mountainArr);    // 1
        int index1 = findElement(target, mountainArr, 0, indexPeak); // 3
        if (index1 != -1)
        {
            return index1;
        }
        else
        {
            return findElement(target, mountainArr, indexPeak + 1, n - 1);
        }
    }
};
// 0,5,3,1
int main()
{
}