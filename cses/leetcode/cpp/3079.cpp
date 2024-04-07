#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int sumOfEncryptedInt(vector<int>& nums) {
    int sum = 0;
        for(int num : nums){
            int maxDigit = -1, l = 0;
            int temp = 0;
            while(num > 0){
                maxDigit = max(maxDigit, num%10);
                num = num/10;
                l++;
            }
            sum += (maxDigit * l);
        }
        return sum;
    }
};
int main()
{

}