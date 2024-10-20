#include <bits/stdc++.h>
using namespace std;
struct Comparator {
    bool operator()(const int a, const int b) const {
        return a > b;
    }
};

class Solution {
private:
    string letters;
    vector<bool> ans;

    bool isPalindrome(const string& s) {
        int l = 0, r = s.size() - 1;
        while (l < r) {
            if (s[l++] != s[r--]) {
                return false;
            }
        }
        return true;
    }

public:
    string dfs(map<int, set<int, Comparator>>& graph, string path, int source, int parent = -1) {
        path.push_back(letters[source]);
        for (auto child : graph[source]) {
            if (child != parent) {
                string s = dfs(graph, "", child, source);
                ans[child] = isPalindrome(s); // Save the path for the child
                path += s; // Append child's path after dfs
            }
        }
        return path;
    }

    vector<bool> findAnswer(vector<int>& parent, const string& s) { 
        letters = s;
        int n = parent.size();
        ans.resize(n);
        map<int, set<int, Comparator>> graph;

        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                graph[parent[i]].insert(i);
            }
        }

        string path = dfs(graph, "", 0);
        ans[0] = isPalindrome(path);
        return ans;
    }
};
