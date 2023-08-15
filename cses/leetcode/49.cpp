
#include <bits/stdc++.h>
using namespace std;

int main()
{
}
class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        unordered_map<size_t, vector<string>> mp;
        for (string s : strs)
        {
            size_t key = getHash(s);
            mp[key].push_back(s);
        }
        vector<vector<string>> res;
        for (auto it : mp)
        {
            res.push_back(it.second);
        }
        return res;
    }

private:
    size_t getHash(string s)
    {
        array<int, 26> count = {0};
        for (char c : s)
        {
            count[c - 'a']++;
        }
        size_t seed = 0;
        for (int i = 0; i < 26; i++)
        {
            seed = seed * 31 + count[i];
        }
        return seed;
    }
};

class Solution2
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> output;    // declare a 2D vector to store the output
        unordered_map<string, int> m_map; // declare an unordered map to store the sorted strings and their corresponding indices in the 'output' vector

        if (strs.size() == 0)
        {
            return {{""}}; // if the input vector is empty, return a 2D vector with a single empty string
        }

        for (int i = 0; i < strs.size(); i++)
        { // loop over each string in the input vector
            string str = strs[i];
            sort(str.begin(), str.end()); // sort the string in alphabetical order

            if (m_map.count(str) > 0)
            {                                          // check if the sorted string already exists in the map
                output[m_map[str]].push_back(strs[i]); // if it does, add the original string to the corresponding vector in 'output'
            }
            else
            {
                output.push_back({strs[i]});    // if it doesn't, add a new vector to 'output' with the current string as the first element
                m_map[str] = output.size() - 1; // also add the sorted string and its index in 'output' to the map
            }
        }
        return output; // return the final 2D vector
    }
};
```

    So the basic idea of this solution is to use a map to keep track of the sorted strings and their corresponding indices in the output vector.Then we loop over each string in the input vector,
    sort it in alphabetical order, and check if the sorted string already exists in the map.If it does, we add the original string to the corresponding vector in the output vector.If it doesn't, we add a new vector to the output vector with the current string as the first element, and also add the sorted string and its index in the output vector to the map. Finally, we return the output vector.
}