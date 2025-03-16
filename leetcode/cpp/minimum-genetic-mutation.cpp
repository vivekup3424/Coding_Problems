#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findDistance(string a, string b){
        int count = 0;
        for(int i = 0; i < min(a.size(),b.size()); i++){
            if(a[i]!=b[i]){
                count++;
            }
        }
        return count;
    }
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        int numBankGenes = bank.size();
        vector<bool> visited(numBankGenes,false);
        queue<pair<string,int>> q;
        q.push({startGene,0});
        while(q.size()>0){
            auto [str,level] = q.front();
            q.pop();
            if(str == endGene){
                return level;
            }
            for(int i = 0; i < numBankGenes; i++){
                if(visited[i]==false and findDistance(str, bank[i])==1){
                    visited[i] = true;
                    q.push({bank[i],level+1});
                }
            }
        }
        return -1;
    }
};
