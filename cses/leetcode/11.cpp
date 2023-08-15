// important
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int n = height.size();
        int i = 0, j = 0, product = 0;
        while (i < n and j < n)
        {
            product = max(product, min(height[i], height[j]) * (j - i));
            if (height[i] < height[j])
                i++;
            else
                j++;
        }
        return product;
    }
};
int main()
{
}