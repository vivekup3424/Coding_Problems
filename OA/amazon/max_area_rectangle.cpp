#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*Q. max area rectangle.. Array of lengths is given. Question is to find maximum sum of areas of rectangle that can be formed using these lengths and length can differ by atmost 1 unit

First sort then pair up length if they are equal or atmax 1 unit differed. then Using these pairs I calculated max sum area by continuously picking up from maximum lengths.
*/

long long maxArea(vector<int> sideLengths)
{
    sort(sideLengths.begin(), sideLengths.end());

    vector<long long> pair;
    int i = sideLengths.size();
    long long ans = 0;

    while (i >= 0)
    {
        if (i > 0 && sideLengths[i] == sideLengths[i - 1])
        {
            pair.push_back(sideLengths[i]);
            i -= 2;
        }
        else if (i > 0 && sideLengths[i] == (sideLengths[i - 1] + 1))
        {
            pair.push_back(sideLengths[i - 1]);
            i -= 2;
        }
        else
        {
            i--;
        }
    }

    for (int i = 0; i < (pair.size() - 1); i += 2)
    {
        ans += pair[i] * pair[i + 1];
    }

    return ans;
}