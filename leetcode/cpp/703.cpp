
#include <bits/stdc++.h>
using namespace std;
class KthLargest
{
public:
    int k;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq; // Use min heap

    KthLargest(int k, std::vector<int> &nums)
    {
        this->k = k;
        for (int i = 0; i < nums.size(); i++)
        {
            pq.push(nums[i]);
            if (pq.size() > k)
            {
                pq.pop(); // Keep the heap size at most k
            }
        }
    }

    int add(int val)
    {
        pq.push(val);
        if (pq.size() > k)
        {
            pq.pop(); // Remove the smallest element if heap size exceeds k
        }
        return pq.top(); // The top of the heap is the kth largest element
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
int main()
{
}