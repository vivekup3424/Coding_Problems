// Corresponds to video number 21 of CP playlist of Luv

// Prefix Computation
// Q.1
#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
// Method 1 Naive
int main1()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N, Q;
        cin >> N >> Q;
        vector<int> A;
        int temp;
        A.push_back(0);
        for (int i = 0; i < N; i++)
        {
            cin >> temp;
            A.push_back(temp);
        }
        // A[0,1,...n]
        while (Q--)
        {
            int L, R;
            cin >> L >> R;
            int gc = 0;
            for (int i = 1; i < L; i++)
            {
                gc = __gcd(gc, a[i]);
            }
            for (int i = r + 1; i <= N; i++)
            {
                gc = __gcd(gc, A[i]);
            }
            cout << gc << "\n";
        }
    }
}
// Time complexity = O(n^3*O(logn)) =>O(n^3logn) logn for __gcd
//=> TLE

// Method 2
// Prefix Computation
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        int N, Q;
        cin >> N >> Q;
        vector<int> A;
        int temp;
        for (int i = 0; i < N; i++)
        {
            cin >> temp;
            A.push_back(temp);
        }
        // A[1,...n] = A[0,1,2...n-1]
        vector<int> forwardGCD(N);
        vector<int> backwardGCD(N);
        int gc = 0;
        for (int i = 0; i < N; i++)
        {
            gc = __gcd(gc, A[i]);
            forwardGCD[i] = gc;
        }
        gc = 0;
        for (int i = N - 1; i >= 0; i--)
        {
            gc = __gcd(gc, A[i]);
            backwardGCD[i] = gc;
        }
        while (Q--)
        {
            int L, R;
            cin >> L >> R;
            int gc = 0;
            for (int i = 1; i < L; i++)
            {
                gc = __gcd(gc, a[i]);
            }
            for (int i = r + 1; i <= N; i++)
            {
                gc = __gcd(gc, A[i]);
            }
            int l = L - 1, r = R - 1;
            int gc1 = forwardGCD[l - 1];
            int gc2 = backwardGCD[r + 1];
            gc = __gcd(gc1, gc2);
            cout << gc << "\n";
        }
    }
}