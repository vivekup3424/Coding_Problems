/**
 * You are given a list of airline tickets where tickets[i] = [fromi, toi] 
 * represent the departure and the arrival airports of one flight. 
 * Reconstruct the itinerary in order and return it.
 * All of the tickets belong to a man who departs from "JFK", 
 * thus, the itinerary must begin with "JFK". If there are
 * multiple valid itineraries, you should return the 
 * itinerary that has the smallest lexical order when 
 * read as a single string.
 *
 *  For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
 *
 *  You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.
*/

#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

class Solution {
private:
    void dfs(unordered_map<string, multiset<string>> &m, string airport,vector<string> &result){
        while(!m[airport].empty()){
            auto it = *m[airport].begin();
            m[airport].erase(it);
            result.push_back(it);
            dfs(m,it,result);
        }
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, multiset<string>> graph;
        int numTickets = tickets.size();
        for(auto ticket : tickets){
            graph[ticket[0]].insert(ticket[1]);
        }
        vector<string> result;
        dfs(graph,"JFK",result);
        return result;
    }
};
