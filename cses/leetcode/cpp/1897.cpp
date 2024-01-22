#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
typedef long long unsigned llu;
typedef std::vector<int> vi; 

inline void fast_io()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
class Solution {
public:
    bool makeEqual(vector<string>& words) {
        int k = words.size();
        unordered_map<char,int> freq;
        for(string word : words){
            for(char c : word){
                freq[c]++;
            }
        }
        for(auto it:  freq){
            if(it.second % k != 0)return false;
        }
        return true;
    }
};
int main()
{
    fast_io();
    int T;
    cin >> T;
    while (T--)
    {
        
        
    }
}