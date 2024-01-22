// do a greedy approach, and check for each element, whether its successor and predecessor are present in the array are '0' or not

#include <bits/stdc++.h>
using namespace std;
#include <vector>

class Solution
{
public:
    bool canPlaceFlowers(std::vector<int> &flowerbed, int n)
    {
        int length = flowerbed.size();
        for (int i = 0; i < length && n > 0; ++i)
        {
            if (flowerbed[i] == 0 && (i == 0 || flowerbed[i - 1] == 0) && (i == length - 1 || flowerbed[i + 1] == 0))
            {
                flowerbed[i] = 1;
                --n;
                // Skip the next plot if it exists (i.e., it's not the last one)
                if (i < length - 1)
                    ++i;
            }
        }
        return n <= 0;
    }
};

int main()
{
}