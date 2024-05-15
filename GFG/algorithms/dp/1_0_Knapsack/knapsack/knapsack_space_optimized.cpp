// A dynamic programming based
// solution for 0-1 Knapsack problem
#include <bits/stdc++.h>
using namespace std;

// A utility function that returns
// maximum of two integers
int max(int a, int b)
{
	return (a > b) ? a : b;
}

// Returns the maximum value that
// can be put in a knapsack of capacity W
int knapSack(int W, int wt[], int val[], int n)
{
	int i, w;
	vector<vector<int>> K(n + 1, vector<int>(W + 1));
    vector<int> prev(W+1,-1);
    vector<int> current(W+1,-1);
	// Build table K[][] in bottom up manner
	for(i = 0; i <= n; i++)
	{
		for(w = 0; w <= W; w++)
		{
			if (i == 0 || w == 0)
				current[w] = 0;
			else if (wt[i - 1] <= w)
				K[i][w] = max(val[i - 1] +
								prev[w - wt[i - 1]],
								prev[w]);
			else
				K[i][w] = prev[w];
		}
        prev = current;
	}
	return K[n][W];
}

// Driver Code
int main()
{
	int val[] = { 60, 100, 120 };
	int wt[] = { 10, 20, 30 };
	int W = 50;
	int n = sizeof(val) / sizeof(val[0]);
	
	cout << knapSack(W, wt, val, n);
	
	return 0;
}

/*Time Complexity: O(N*W). 
Auxiliary Space: O(N*W). */

