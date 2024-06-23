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
// Fills lps[] for given pattern pat[0..M-1]
void computeLPSArray(const string& pat, vector<int>& lps) {
    int M = pat.length();
    int len = 0;
    int i = 1;
    lps[0] = 0;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Counts occurrences of pat in txt using KMP algorithm
int find_num_occurences(const string& text, const string& pattern) {
    int M = pattern.length();
    int N = text.length();
    vector<int> lps(M);

    computeLPSArray(pattern, lps);

    int count = 0;
    int i = 0, j = 0;
    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }
        if (j == M) {
            count++;
            j = lps[j - 1];
        } else if (i < N && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return count;
}

int main()
{
    fast_io();
    ll T;
    std::cin >> T;
    while (T--)
    {
        ll n;
        cin>>n;
        string s;
        cin>>s;
        ll a = find_num_occurences(s,"map");
        ll b = find_num_occurences(s,"pie");
        ll c = find_num_occurences(s,"mapie");
        cout<<a+b-c<<endl;   
    }
}
