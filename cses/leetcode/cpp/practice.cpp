#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long unsigned llu;
typedef std::vector<int> vi;
typedef std::vector<long long> vll;

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

class Solution {
public:
    long long maximumHappinessSum(vector<int>& happiness, int k) {
        priority_queue<int, vector<int>> maxHeap;
        for(int i: happiness){
            maxHeap.push(i);
        }
        int count = 0;
        long long sum = 0;
        while(k-- and maxHeap.size()>0){
            sum += max(0, maxHeap.top()-count);
            count++;
        }
        return sum;
    }
};

int main()
{
    fast_io();
    vector<int>v = {1,2,3};
    int k = 2;
    Solution A;
    ll m = A.maximumHappinessSum(v,k);
}
