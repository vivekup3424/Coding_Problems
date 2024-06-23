
#include <bits/stdc++.h>
using namespace std;
// since there need to be O(n) time complexity, hence I can use sorting algo or anything like that to get
// a definite order in which numbers come

// 2. Hence I can make use of min-heap, time-complexity of building a min-heap is O(n)
// after that I can keep popping the element with O(logn) complexity , and check for consecutive elements
class Solution1
{
    // I thought of this solution by myself
public:
    int longestConsecutive(vector<int> &nums)
    {
        if (nums.size() == 0)
        {
            return 0;
        }
        // min-heap
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (int n : nums)
        {
            minHeap.push(n);
        }
        int length = 0, max_length = 1, prev_element = -1;
        while (minHeap.empty() == false)
        {
            if (length == 0)
            {
                prev_element = minHeap.top();
                minHeap.pop();
                length = 1;
            }
            else
            {
                while (minHeap.empty() == false and
                       minHeap.top() == prev_element)
                {
                    minHeap.pop();
                }
                if (minHeap.empty() == false)
                {
                    int temp = minHeap.top();
                    minHeap.pop();
                    if ((temp - prev_element) == 1)
                    {
                        length++;
                    }
                    else
                    {
                        length = 1;
                    }
                    max_length = max(max_length, length);
                    prev_element = temp;
                }
            }
        }
        return max_length;
    }
};

class Solution2
{
    // using hashsets or simply set, using union-find method
public:
    int longestConsecutive(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> size(n, 1);
        map<int, int> parent;
    }
};
int main()
{
    // Example usage
    vector<int> nums = {0, 0};
    Solution1 sol;
    int longest = sol.longestConsecutive(nums);
    cout << "Longest consecutive sequence: " << longest << endl;

    return 0;
}