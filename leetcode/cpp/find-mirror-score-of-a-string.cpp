#include <bits/stdc++.h>
using namespace std;

class Solution{
public:
    long long calculateScore(string s){
        long long score = 0;
        int n = s.length();
        map<char,stack<int>> indices;
        for(int i = 0; i < n; i++){
            char complement = 25 - (s[i]-'a') + 'a';
            indices[s[i]].push(i);
            if(indices.count(complement)){
                score += abs(indices[complement].top() - indices[s[i]].top());
                indices[complement].pop();
                indices[s[i]].pop();
                if(indices[complement].size()==0){
                    indices.erase(complement);
                }
                if(indices[s[i]].size()==0){
                    indices.erase(s[i]);
                }
            }
        }
        return score;
    }
};

//making improvements, by using a vector rather than a map
//hence search operation would reduce from logarithmic to constant
//time complexity

#include <bits/stdc++.h>
using namespace std;

class Solution2{
public:
    long long calculateScore(string s){
        long long score = 0;
        int n = s.length();
        vector<stack<int>> indices(26);
        for(int i = 0; i < n; i++){
            int complement = 25 - (s[i]-'a');
            indices[s[i]-'a'].push(i);
            if(indices[complement].size()>0){
                score += abs(indices[complement].top() - indices[s[i]].top());
                indices[complement].pop();
                indices[s[i]].pop();
            }
        }
        return score;
    }
};


