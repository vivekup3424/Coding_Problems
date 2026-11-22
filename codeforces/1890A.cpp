/*
 * 1890A. Doremy's Paint 3
 * https://codeforces.com/problemset/problem/1890/A
 * Time limit: 1 second | Memory limit: 256 megabytes
 *
 * An array b_1, b_2, ..., b_n of positive integers is good if all the sums
 * of two adjacent elements are equal to the same value. More formally, the
 * array is good if there exists a k such that
 * b_1 + b_2 = b_2 + b_3 = ... = b_{n-1} + b_n = k.
 *
 * Doremy has an array a of length n. Now Doremy can permute its elements
 * (change their order) however she wants. Determine if she can make the
 * array good.
 *
 * Input:
 *   The input consists of multiple test cases. The first line contains a
 *   single integer t (1 <= t <= 100) - the number of test cases. The
 *   description of the test cases follows.
 *
 *   The first line of each test case contains a single integer n
 *   (2 <= n <= 100) - the length of the array a.
 *
 *   The second line of each test case contains n integers
 *   a_1, a_2, ..., a_n (1 <= a_i <= 10^5).
 *
 *   There are no constraints on the sum of n over all test cases.
 *
 * Output:
 *   For each test case, output "Yes" (without quotes), if it is possible to
 *   reorder the elements of a to make the array good, and "No" otherwise.
 *
 *   You can output "Yes" and "No" in any case.
 *
 * Example 1
 *   Input:
 *     5
 *     2
 *     8 9
 *     3
 *     1 1 2
 *     4
 *     1 1 4 5
 *     5
 *     2 3 3 3 3
 *     4
 *     100000 100000 100000 100000
 *   Output:
 *     Yes
 *     Yes
 *     No
 *     No
 *     Yes
 *
 * Note:
 *   In the first test case, [8, 9] and [9, 8] are good.
 *
 *   In the second test case, [1, 2, 1] is good because
 *   a_1 + a_2 = a_2 + a_3 = 3.
 *
 *   In the third test case, it can be shown that no permutation is good.
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int main()
{
    fast_io();
    ll T;
    cin >> T;
    while (T--)
    {
        int n;
        cin>>n;
        map<int,int> freq;
        for (auto i = 0; i < n; i++)
        {
            int temp;
            cin>>temp;
            freq[temp]++;
        }
        if(freq.size()>2){
            cout<<"No"<<endl;
        }
        else if(freq.size()==2){
            int f1 = freq.begin()->second; //freq of first key
            int f2 = freq.rbegin()->second; //freq of second key
            int diff = abs(f1 - f2);
            cout<<(diff <= 1 ? "Yes" : "No")<<endl;
        }
        else{
            cout<<"Yes"<<endl;
        }
        
    }
}
