#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        unordered_map<string,int> indices;
        for(auto i = 0;i < req_skills.size();i++){
            indices[req_skills[i]] = i;
        }
        

    }
};