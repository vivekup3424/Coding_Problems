// first sort the list, and then use two pointer start = 0, end = n-1, to check for pairs with sum = k,
// but you imrpove this further by introducing a hashmap and soliving it like a 2Sum problem
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int maxOperations(vector<int> &nums, int k)
    {
        sort(nums.begin(), nums.end());
        int start = 0, end = nums.size() - 1;
        int count = 0;
        while (start < end)
        {
            int sum = nums[start] + nums[end];
            if (sum == k)
            {
                count++;
                start++;
                end--;
            }
            else if (sum < k)
            {
                start++;
            }
            else
            {
                end--;
            }
        }
        return count;
    }
    // Since we are using sorting and two-pointers approach, hence
    // Time complexity = O(nlogn)+O(n)=O(nlogn)
    // Space complexity = O(1)
};

// better approach
/*But, by looking at that, interviewer will say. I'm still not happy, so give him a flying kiss I mean give him a better solution 😅

Now again, perform a beautiful acting, and say why dont we use MAP. So, tell him by using map, we can optimise it more beautifully.
So, what we'll gonna do is & may be you know this one, it is similar to Two Sum, so if u dont know then listen to me.

We gonna fill our map as frequency map. And we gonna get the result by subtracting current value from k & whatever result we get, we gonna check in our map. If that is present increment the count & remove it from the map now. That's how we'll get our answer in just O(1) for searching & as we are using a loop thus, O(N). But it's a good approach.
*/
class Solution
{
public
    int maxOperations(int[] nums, int k)
    {
        Map<Integer, Integer> map = new HashMap<>();
        int count = 0;
        for (int i = 0; i < nums.length; i++)
        {
            int res = k - nums[i];
            if (map.containsKey(res))
            {
                count++;
                if (map.get(res) == 1)
                    map.remove(res);
                else
                    map.put(res, map.get(res) - 1);
            }
            else
            {
                map.put(nums[i], map.getOrDefault(nums[i], 0) + 1);
            }
        }
        return count;
    }
} int main()
{
}