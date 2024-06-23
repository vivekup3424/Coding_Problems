#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct MostCommonWord
{
    int freq;
    string word;
};
char toLowercase(char c)
{
    if (c >= 'A' and c <= 'Z')
    {
        return char(c - 'A' + 'a');
    }
    return c;
}
bool isAlpha(char c)
{
    if (c >= 'a' and c <= 'z')
    {
        return true;
    }
    else if (c >= 'A' and c <= 'Z')
    {
        return true;
    }
    return false;
}
class Solution
{
public:
    string mostCommonWord(string paragraph, vector<string> &banned)
    {
        map<string, int> freqHashMap;
        string temp = "";
        for (int i = 0; i < paragraph.size(); i++)
        {
            if (isAlpha(paragraph[i]) == false)
            {
                if (temp.length() > 0)
                {
                    freqHashMap[temp]++;
                }
                temp = "";
            }
            else
            {
                temp.push_back(toLowercase(paragraph[i]));
            }
        }
        if (temp.length() > 0)
        {
            freqHashMap[temp]++;
        }
        set<string> bannedWords;
        for (string word : banned)
        {
            bannedWords.insert(word);
        }
        // get the most common word
        MostCommonWord w;
        w.freq = 0;
        w.word = "";
        for (auto it : freqHashMap)
        {
            if (bannedWords.count(it.first) == 0)
            {
                if (w.freq < it.second)
                {
                    w.word = it.first;
                    w.freq = it.second;
                }
            }
        }
        return w.word;
    }
};