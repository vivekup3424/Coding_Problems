#include <bits/stdc++.h>
using namespace std;

int binarySearch(vector<int> arr,int l, int r, int target){
    if(l > r)return -1;
    else
    {
        int mid = l + (r-l)/2;
        if(arr[mid]==target)return mid;
        else if(arr[mid]> target){
            return binarySearch(arr, l, mid-1,target);
        }
        else{
            return binarySearch(arr,mid+1,r,target);
        }
        
    }
}

int search_infinite_sorted_array(vector<int> arr, int target)
{
    int l = 0, r = 1;
    while(target > arr[r]){
        l = r;
        r = 2 * r;
    }
    return binarySearch(arr, l,r,target);
}