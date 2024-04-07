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
    string smallestLexicographicString(const string& s1, const string& s2) {
    // Use the comparison operators to determine the lexicographically smallest string
    if (s1 < s2) {
        return s1;
    } else {
        return s2;
    }
    }      
    map<string,int> generateSubstrings(string s){
    int n = s.size();
    map<string,int> substrings;
    for(int i = 0; i < n; i++){
        string temp;
        for(int j = i; j < n; j++){
            temp.push_back(s[j]);
            substrings[temp]++;
        }
    }
    //time complexity = O(n^2)
    return substrings;
}
    vector<string> shortestSubstrings(vector<string>& arr) {
        int n = arr.size();
        map<string,int> TotalSubstrings;
        vector<map<string,int>> substringsMap(n); //maps the indices to the map 
        //of substrigs for the string
        //1. generate substrings for every string in the arr
        for(int i = 0;i < n; i++){
            string s = arr[i];
            int m = s.size();
            map<string, int>substrings=generateSubstrings(s);
            //2. add the substrings of every strings to the totalsubstring
            for(auto it:substrings){
                TotalSubstrings[it.first] += it.second;
                //time complexity = O(n * m^2)
            }
            substringsMap[i] = substrings;
        }

        //since map is already sorted in lexographically increasing order
        // for every substrings in a particular strings, check if exists in other 
        //strings or not
        vector<string> ans(n,"");

        for(int i = 0; i < n; i++){
            map<string,int> substring = substringsMap[i];
            for(auto it: substring){
                if(it.second == TotalSubstrings[it.first]){
                    //substring unique to a given string
                    if(ans[i]==""){
                        ans[i] = it.first;
                    }
                    else if(it.first.length() < ans[i].length()){
                        ans[i] = it.first;
                    }
                    else if(it.first < ans[i]){
                        ans[i] = it.first;
                    }
                }
            }
        }
        return ans;
    }
};

int main()
{
    fast_io();
    vector<string> arr = {"gfnt","xn","mdz","yfmr","fi","wwncn","hkdy"};
    Solution A;
    vector<string> ans = A.shortestSubstrings(arr);
}
