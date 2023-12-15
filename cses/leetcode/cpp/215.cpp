class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;

        for (int num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        return pq.top();
    }
};

    The function findKthLargest takes in a vector of integers nums and an integer k as parameters. It returns the Kth largest element in the array.

    The code declares a priority queue pq that will store the K largest elements in a min-heap fashion. The priority queue is declared with the type int, a vector as the underlying container, and the greater<int> comparator. This means that the smallest element will be at the top of the priority queue.

    The code iterates through each element num in the nums vector.

    For each element num, it pushes it into the priority queue pq.

    After inserting the element, the code checks if the size of the priority queue exceeds k. If it does, it removes the smallest element by calling pq.pop(). This ensures that the priority queue only contains the K largest elements.

    After iterating through all the elements in nums, the code returns the top element of the priority queue, which is the Kth largest element.

To summarize, the code uses a min-heap (implemented as a priority queue) to efficiently find the Kth largest element in the array. By keeping the priority queue size restricted to k, it guarantees that the top element will be the Kth largest element.
