
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = nums.size();
        //maxElement = n-1
        vector<int> freqArray (n,0); //1-indexed array [0,1,2,3,...n-1] //ignore 0 here
        for(int i = 0;i<n;i++)
        {
            freqArray[nums[i]] +=1;
        }
        for(int i = 1;i<n;i++)
        {
            if(i == n-1)
            {
                if(freqArray[i] != 2)return false;
            }
            else if(freqArray[i]!=1)
            {
                return false;
            }
        }
        return true;
    }
};
int main()
{
    
}