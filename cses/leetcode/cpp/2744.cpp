
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    int maximumNumberOfStringPairs(vector<string>& words) {
        int maxSum = 0;
        unordered_set<string> s;
        for (string const& word : words) {
            string temp = word;
            reverse(temp.begin(), temp.end());
            if (s.count(temp)) {
                maxSum++;
                s.erase(temp);
            } else {
                s.insert(word);
            }
        }
        return maxSum;
    }
};
int main()
{
    
}