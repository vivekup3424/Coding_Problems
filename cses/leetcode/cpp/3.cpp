
#include <bits/stdc++.h>
using namespace std;
class Solution2
{
public:
    int lengthOfLongestSubstring(string s)
    {
        unordered_map<char, int> char_index_map;
        int n = s.length();
        int start = 0, end = 0, max_len = 0; // indices
        for (int i = 0; i < n; i++)
        {
            if (char_index_map.count(s[i]) && char_index_map[s[i]] >= start)
            {
                start = char_index_map[s[i]] + 1;
            }
            char_index_map[s[i]] = i;
            end = i;
            max_len = max(max_len, end - start + 1);
        }
        return max_len;
    }
};
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char,int> char_index_map;
        int start = 0, end = 0, max_len = 0,n = s.length();
        for(int i = 0;i<n;i++)
        {
            if(char_index_map[s[i]] && char_index_map[s[i]]>=start)
            {
                start = char_index_map[s[i]]+1;
            }
            char_index_map[s[i]] = i;
            end = i;
            max_len = max(max_len,(end-start+1));
        }
        return max_len;
    }
};


