
#include <bits/stdc++.h>
using namespace std;
/**Method 1: Using dp and sorting
1. Sort the pairs based on the second element in each pair.
2. Initialize:
   - n as the number of pairs.
   - Create an array dp of size n + 1 to store the length of the chain ending at each pair.
   - Initialize maxLength as 1 (minimum possible chain length) and secondElement as the second element of the first pair.

3. Loop through the pairs starting from the second pair (i = 1 to n):
   a. If i is 1:
      - Set dp[i] to 1.
   b. Else:
      - Check if secondElement < pairs[i - 1][0]:
         - If true, set dp[i] to dp[i - 1] + 1 (extend the chain).
         - Update secondElement to pairs[i - 1][1].
      - Else, set dp[i] to dp[i - 1] (chain length remains the same).

   c. Update maxLength with max(dp[i], maxLength).

4. Return maxLength as the maximum length of the pair chain.

End.

*/
class Solution
{
public:
    static bool compareVectors(const vector<int> &a, const vector<int> &b)
    {
        return a[1] < b[1];
    }
    int findLongestChain(vector<vector<int>> &pairs)
    {
        sort(pairs.begin(), pairs.end(), compareVectors);
        int n = pairs.size();
        int dp[n + 1];
        int maxLength = 1, secondElement = pairs[0][1];
        for (int i = 1; i <= n; i++)
        {
            if (i == 1)
            {
                dp[i] = 1;
            }
            else
            {
                if (secondElement < pairs[i - 1][0])
                {
                    dp[i] = dp[i - 1] + 1;
                    secondElement = pairs[i - 1][1];
                }
                else
                {
                    dp[i] = dp[i - 1];
                }
            }
            maxLength = max(dp[i], maxLength);
        }
        return maxLength;
    }
    // Time complexity = O(nlogn) + O(n) , where n = pairs.size()
    // Space Complexity = O(1)
};
int main()
{
}