/* Given an array of n integers, your task is to process q queries of the following types:

    *update the value at position k to u
    *what is the sum of values in range [a,b]
?*/

// Method 1: Using Segment Tree

// The total time it takes to build a segment tree is O(n)
// and the total time it takes to answer a query is O(logn).
// So, the total time complexity is O(n+qlogn).

// PsuedoCode for segment tree
int f(int node, int query_low, int query_high)
{
    if (this node is completely within interval[query_low, query_high])
        r
        {
            return tree[node]
        }
    else if (this node is disjoint with interval[query_low, query_high])
    {
        return 0;
    }
    else
    {
        return f(left_child, query_low, query_high) +
               f(right_child, query_low, query_high)
    }
}