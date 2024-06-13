/* Dynamic Programming implementation of LCS problem */
// print the longest common subsequence
#include <bits/stdc++.h>
using namespace std;

string printLCS(string x, string y)
{
	int a = x.size(), b = y.size();
	int t[a + 1][b + 1];
	memset(t, -1, (a + 1) * (b + 1));
	for (int i = 0; i < a + 1; i++)
	{
		for (int j = 0; j < b + 1; j++)
		{
			if (i == 0 || j == 0)
				t[i][j] = 0; // initialization
			else if (x[i - 1] == y[j - 1])
			{
				t[i][j] = 1 + t[i - 1][j - 1];
			}
			else
			{
				t[i][j] = max(t[i - 1][j], t[i][j - 1]);
			}
		}
	}
	string s;
	int i = a, j = b;
	while (i > 0 and j > 0)
	{
		if (x[i - 1] == y[j - 1])
		{
			s.push_back(x[i - 1]);
			i--;
			j--;
		}
		else
		{
			if (t[i - 1][j] > t[i][j - 1])
			{
				i = i - 1;
				// j = j
			}
			else
			{
				// i = i;
				j = j - 1;
			}
		}
	}
	string lcs;
	for (int i = s.size() - 1; i >= 0; i--)
	{
		lcs.push_back(s[i]);
	}
	cout << lcs << "\n";
	return lcs;
}

/* Driver program to test above function */
int main()
{
	string X = "AGGTAB";
	string Y = "GXTXAYB";
	printLCS(X, Y);
	return 0;
}
