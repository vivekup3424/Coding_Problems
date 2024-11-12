#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    string alienOrder(vector<string>& words) {
        map<char,set<char>> graph;
        map<char,int> indegree;
        queue<char> start;
        for(auto word : words){
            for(char c : word){
                indegree[c] = 0;
            }
        }
        for(int i = 1; i < words.size(); i++){
            string prev = words[i-1];
            string current = words[i];
            for(int j = 0; j < min(prev.size(),current.size()); j++){
                if(prev.size()>current.size() and prev.substr(0,current.size())==current){
                    return "";
                }
                if(prev[j]!=current[j]){
                    if(graph[prev[j]].find(current[j])==graph[prev[j]].end()){
                        graph[prev[j]].insert(current[j]);
                        indegree[current[j]]++;
                    }
                    break;
                }
            }
        }
        cout<<"Resultant graph:-"<<endl;
        for(auto it : graph){
            cout<<it.first<<"=>\t";
            for(auto i : it.second){
                cout<<i<<", ";
            }
            cout<<endl;
        }
        cout<<"Indegree maps:-\n";
        for(auto it : indegree){
            cout<<it.first<<"->"<<it.second<<endl;
        }
        for(auto it : indegree){
            if(it.second==0){
                start.push(it.first);
            }
        }
        string answer;
        while(start.size()>0){
            char node = start.front();
            answer.push_back(node);
            start.pop();
            for(auto c : graph[node]){
                indegree[c]--;
                if(indegree[c]==0){
                    start.push(c);
                }
            }
        }
        return answer.size() == graph.size() ? answer : "";
    }
};
