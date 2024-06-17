#include <bits/stdc++.h>
using namespace std;

class SegmentTree
{
private:
    vector<int> tree; // Segment tree array
    vector<int> lazy; // Lazy propagation array
    int n;            // Size of the input array

    // Function to build the segment tree
    void build(const vector<int> &arr, int node, int start, int end)
    {
        if (start == end)
        {
            // Leaf node, store the value from the array
            tree[node] = arr[start];
        }
        else
        {
            int mid = (start + end) / 2;
            // Recursively build the left and right subtrees
            build(arr, 2 * node, start, mid);
            build(arr, 2 * node + 1, mid + 1, end);
            // Internal node will have the sum of both children
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    // Function to update a single element
    void update(int node, int start, int end, int idx, int val)
    {
        if (start == end)
        {
            // Leaf node, update the value
            tree[node] = val;
        }
        else
        {
            int mid = (start + end) / 2;
            // Determine which subtree to update
            if (start <= idx && idx <= mid)
            {
                update(2 * node, start, mid, idx, val);
            }
            else
            {
                update(2 * node + 1, mid + 1, end, idx, val);
            }
            // Update the current node's value
            tree[node] = tree[2 * node] + tree[2 * node + 1];
        }
    }

    // Function to query the sum in a range
    int query(int node, int start, int end, int L, int R)
    {
        if (R < start || end < L)
        {
            // Range completely outside the current segment
            return 0;
        }
        if (L <= start && end <= R)
        {
            // Range completely inside the current segment
            return tree[node];
        }
        // Partially inside and partially outside
        int mid = (start + end) / 2;
        int left_query = query(2 * node, start, mid, L, R);
        int right_query = query(2 * node + 1, mid + 1, end, L, R);
        return left_query + right_query;
    }

    // Function to update a range with lazy propagation
    void updateRange(int node, int start, int end, int L, int R, int val)
    {
        if (lazy[node] != 0)
        {
            // There are pending updates, apply them
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start > end || start > R || end < L)
        {
            // Out of range
            return;
        }
        if (start >= L && end <= R)
        {
            // Current segment is fully within range
            tree[node] += (end - start + 1) * val;
            if (start != end)
            {
                lazy[2 * node] += val;
                lazy[2 * node + 1] += val;
            }
            return;
        }
        // Partially inside and partially outside
        int mid = (start + end) / 2;
        updateRange(2 * node, start, mid, L, R, val);
        updateRange(2 * node + 1, mid + 1, end, L, R, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    // Function to query a range with lazy propagation
    int queryRange(int node, int start, int end, int L, int R)
    {
        if (lazy[node] != 0)
        {
            // There are pending updates, apply them
            tree[node] += (end - start + 1) * lazy[node];
            if (start != end)
            {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = 0;
        }
        if (start > end || start > R || end < L)
        {
            // Out of range
            return 0;
        }
        if (start >= L && end <= R)
        {
            // Current segment is fully within range
            return tree[node];
        }
        // Partially inside and partially outside
        int mid = (start + end) / 2;
        int left_query = queryRange(2 * node, start, mid, L, R);
        int right_query = queryRange(2 * node + 1, mid + 1, end, L, R);
        return left_query + right_query;
    }

public:
    // Constructor to initialize the segment tree
    SegmentTree(const vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        lazy.resize(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    // Public function to update a single element
    void update(int idx, int val)
    {
        update(1, 0, n - 1, idx, val);
    }

    // Public function to query the sum in a range
    int query(int L, int R)
    {
        return query(1, 0, n - 1, L, R);
    }

    // Public function to update a range of elements
    void updateRange(int L, int R, int val)
    {
        updateRange(1, 0, n - 1, L, R, val);
    }

    // Public function to query the sum in a range with lazy propagation
    int queryRange(int L, int R)
    {
        return queryRange(1, 0, n - 1, L, R);
    }
};

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5};
    SegmentTree st(arr);

    // Test updates and queries
    cout << st.query(0, 2) << endl; // Sum from index 0 to 2
    st.update(1, 10);               // Update index 1 to 10
    cout << st.query(0, 2) << endl; // Sum from index 0 to 2

    // Test range updates and queries with lazy propagation
    st.updateRange(0, 3, 5);             // Add 5 to all elements from index 0 to 3
    cout << st.queryRange(0, 4) << endl; // Sum from index 0 to 4

    return 0;
}
