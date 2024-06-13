#include <bits/stdc++.h>
using namespace std;

int CountSubsetSum(vector<int>& arr, int val, int n)
{
	int count = 0;
	vector<int> PresentState(val + 1, 0),
		LastState(val + 1, 0);
	// consider only last and present state we dont need the
	// (present-2)th state and above and we know for val to
	// be 0 if we dont pick the current index element we can
	// achieve
	PresentState[0] = LastState[0] = 1;
	if (arr[0] <= val)
		LastState[arr[0]] = 1;
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= val; j++)
			PresentState[j]
				= ((j >= arr[i]) ? LastState[j - arr[i]]
								: 0)
				+ LastState[j];
		// this we will need in the next iteration so just
		// swap current and last state.
		LastState = PresentState;
	}
	// Note after exit from loop we will having a present
	// state which is nothing but the laststate itself;
	return PresentState[val]; // or return
							// CurrentState[val];
}
int main()
{
	vector<int> arr = { 3, 3, 3, 3 };
	cout << CountSubsetSum(arr, 6, arr.size());
}
