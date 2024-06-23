#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    long long minEnd(int n, int x)
    {
        // convert x into a vector of bits
        int number = log2(x) + 1;
        // covert number to binary form
        vector<int> binaryNum;
        for (; number > 0; number >>= 1)
        {
            binaryNum.push_back(number % 2);
        }
        reverse(binaryNum.begin(), binaryNum.end());
        vector<int> answer;
        int l = 0;
        for (; x > 0; x >>= 1)
        {
            if (x % 2 == 0)
            {
                binaryNum.push_back(binaryNum[l++]);
            }
        }
    }
};