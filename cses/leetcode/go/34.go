package main

func searchRange(nums []int, target int) []int {
    ans := make([]int,2)
    n := len(nums)
    //finding the lower-bound of occurence
    leftValue := n
    for l,r := 0,n-1; l <= r; {
        mid := (l+r)/2
        if  (nums[mid]==target){
            leftValue = min(leftValue,mid)
            l = mid-1
        }
        else if(nums[mid]<target){
            r = mid+1
        }
    }
    return ans  
}
