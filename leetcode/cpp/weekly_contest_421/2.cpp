#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void visualizeTransformation(unordered_map<char,int>& freq, int step) {
        cout << "After transformation " << step << ":\n";
        string viz;
        // Convert frequency map to actual string for visualization
        for(auto it : freq) {
            viz += string(it.second, it.first);
        }
        // Sort for consistent visualization
        sort(viz.begin(), viz.end());
        cout << "String: " << viz << "\n";
        cout << "Length: " << viz.length() << "\n";
        cout << "Character frequencies:\n";
        vector<pair<char,int>> sortedFreq(freq.begin(), freq.end());
        sort(sortedFreq.begin(), sortedFreq.end());
        for(auto it : sortedFreq) {
            cout << it.first << ": " << it.second << " times\n";
        }
        cout << "------------------------\n";
    }

    int lengthAfterTransformations(string s, int t, bool visualize = true) {
        const int MOD = 1e9 + 7;
        unordered_map<char,int> freq;
        
        // Initial state
        for(auto c : s) {
            freq[c]++;
        }
        
        int prevLength = s.length();
        if(visualize) {
            cout << "Initial state:\n";
            visualizeTransformation(freq, 0);
        }
        
        int step = 1;
        while(t--) {
            unordered_map<char,int> temp;
            for(auto it : freq) {
                if(it.first == 'z') {
                    temp['a'] = (temp['a'] + it.second) % MOD;
                    temp['b'] = (temp['b'] + it.second) % MOD;
                }
                else {
                    temp[it.first + 1] = (temp[it.first + 1] + it.second) % MOD;
                }
            }
            freq = temp;
            
            // Calculate current length
            int currentLength = 0;
            for(auto it : freq) {
                currentLength = (currentLength + it.second) % MOD;
            }
            
            if(visualize && currentLength != prevLength) {
                visualizeTransformation(freq, step);
                prevLength = currentLength;
            }
            step++;
        }
        
        int count = 0;
        for(auto it : freq) {
            count = (count + it.second) % MOD;
        }
        return count;
    }
};

int main() {
    Solution sol;
    
    // Test with a string containing 'z' to see more length changes
    string s = "abczz";  
    cout << "\n=== Testing with t = 26 ===\n";
    sol.lengthAfterTransformations(s, 26, true);
    
    cout << "\n=== Testing with t = 42 ===\n";
    sol.lengthAfterTransformations(s, 42, true);
    
    return 0;
}
