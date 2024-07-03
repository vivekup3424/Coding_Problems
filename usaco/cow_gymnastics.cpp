/**
 *In each of K practice sessions (1≤K≤10), Bessie ranks the N cows according to their performance (1≤N≤20

). Afterward, she is curious about the consistency in these rankings. A pair of two distinct cows is consistent if one cow did better than the other one in every practice session.

Help Bessie compute the total number of consistent pairs.

INPUT FORMAT (file gymnastics.in):
The first line of the input file contains two positive integers K
and N. The next K lines will each contain the integers 1…N in some order, indicating the rankings of the cows (cows are identified by the numbers 1…N). If A appears before B in one of these lines, that means cow A did better than cow B.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    int k, n;
    cin >> k >> n;
    vector<vector<int>> v(k, vector<int>(n));
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> v[i][j];
        }
    }
    return 0;
}
