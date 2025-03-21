#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minJumps(int arr[], int n)
    {

        // The number of jumps needed to
        // reach the starting index is 0
        if (n <= 1)
            return 0;

        // If value of first index guarantees
        // only 1 jump is needed, return 1
        if (arr[0] >= n - 1)
            return 1;

        // Return -1 if not possible to jump
        if (arr[0] == 0)
            return -1;

        // initialization
        // stores all time the maximal
        // reachable index in the array.
        int maxReach = arr[0];

        // stores the number of steps
        // we can still take
        int step = arr[0];

        // stores the number of jumps
        // necessary to reacach that maximal
        // reachable position.
        int jump = 1;

        // Start traversing array
        int i = 1;
        for (i = 1; i < n; i++)
        {
            // Check if we have reached the end of the array
            if (i == n - 1)
                return jump;

            // Check if value at current index guarantees jump to end
            if (arr[i] >= (n - 1) - i)
                return jump + 1;

            // updating maxReach
            maxReach = max(maxReach, i + arr[i]);

            // we use a step to get to the current index
            step--;

            // If no further steps left
            if (step == 0)
            {
                // we must have used a jump
                jump++;

                // Check if the current index/position or lesser index
                // is the maximum reach point from the previous indexes
                if (i >= maxReach)
                    return -1;

                // re-initialize the steps to the amount
                // of steps to reach maxReach from position i.
                step = maxReach - i;
            }
        }

        return -1;
    }
};