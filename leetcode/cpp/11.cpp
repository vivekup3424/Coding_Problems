// important
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        vector<int> arr = height.size(12,0);
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
    int maxArea2(vector<int> &height){
        int n = height.size();
        int i = 0, j = n-1;
        int maxProduct = 0;
        while(i<=j){
            maxProduct = max(maxProduct, min(height[i], height[j]) * (j-i));
            if(height[i] < height[j]){
                i++;
            }else{
                j--;
            }
        }
        return maxProduct;
    }
};
int main()
{
}
