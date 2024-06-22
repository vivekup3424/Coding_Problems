#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;
typedef std::vector<vector<long long>> vvll;
const int MOD = 1e9 + 7;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n)
{
    v.resize(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << v[i] << " ";
    }
    cout << "\n";
}

class Solution
{
public:
    int numberOfSubarrays(vector<int> &nums, int k)
    {
        int start = 0, end = 0, n = nums.size(), count = 0;
        int numOdds = 0;
        // get the first window with k odd numbers
        while (end < n && numOdds < k)
        {
            if (nums[end] % 2 == 1)
            {
                numOdds++;
            }
            end++;
        }
        while (end < n)
        {
            while (numOdds >= k)
            {
                if (numOdds == k)
                {
                    count++;
                }
                if (nums[start] % 2 == 1)
                {
                    numOdds--;
                }
                start++;
            }
            if (nums[end] % 2 == 1)
            {
                numOdds++;
            }
            end++;
        }
        return count;
    }
};
int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n, k;
        cin >> n >> k;
        vi v(n);
        inputVector(v, n);
        cout << Solution().numberOfSubarrays(v, k) << endl;
    }
}