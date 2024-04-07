#include <bits/stdc++.h>
using namespace std;

class Solution1 {
public:
    bool isIsomorphic(string s, string t) {
    //let's construct a maxHeap frequency for both strings
    map<char,int> f1,f2;
    for(char c: s){
        f1[c]++;
    }
    for(char c: t){
        f2[c]++;
    }
    if(f1.size()!=f2.size())return false;
    priority_queue<pair<int,char>,vector<pair<int,char>>> m1,m2;
    for(auto it: f1){
        m1.push({it.second,it.first});
    }  
    for(auto it: f2){
        m2.push({it.second, it.first});
    }
    bool result = true;
    while(m1.size()>0 and m2.size()>0)
    {
        if(m1.top().first != m2.top().first)
        {
            result = false;
            break;
        }
        else{
            m1.pop();
            m2.pop();
        }
    }
    return result;
    }
};
class Solution{
public:
    bool isIsomorphic(string s, string t) {
        map<char,char> m;
        int n = s.size();
        if(s.size()!=t.size())return false;
        for (int i = 0; i < n; i++)
        {
            m[s[i]] = t[i];
        }
        set<char> mappers;
        for(auto it: m){
            mappers.insert(it.second);
        }
        if(mappers.size()!=m.size())return false;
        string ans = "";
        for(char c: s){
            ans.push_back(m[c]);
        }
        return ans == t;
    }
};
int main()
{
    Solution *A = new Solution();
    string s=  "paper";
    string t = "title";
    bool result = A->isIsomorphic(s,t);
}