#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
class Solution1
{
    // think of the most simple approach
public:
    void findWords(string &s, vector<string> &wordDict,
                   vector<string> &words, string word,
                   string temp, int i, int n)
    {
        if (i == n)
        {
            if (find(wordDict.begin(), wordDict.end(), temp) != wordDict.end() or temp == "")
            {
                word = word + " " + temp;
                words.push_back(word);
                return;
            }
            else
            {
                return;
            }
        }

        while (i < n)
        {
            temp.push_back(s[i]);
            i++;
            if (find(wordDict.begin(), wordDict.end(), temp) != wordDict.end())
            {
                // add the word in my string
                string word2 = word;
                word2 = word2 + " " + temp;
                findWords(s, wordDict, words, word2, "", i, n);
            }
        }
    }
    vector<string> wordBreak(string s, vector<string> &wordDict)
    {
        vector<string> words;
        string word;
        int n = s.size();
        findWords(s, wordDict, words, word, "", 0, n);
        // trim the words
        vector<string> trimmedWords;
        for (string w : words)
        {
            int l = 0, r = w.size() - 1;
            while (w[l] == ' ')
            {
                l++;
            }
            while (w[r] == ' ')
            {
                r--;
            }
            string temp;
            for (int i = l; i <= r; i++)
            {
                temp.push_back(w[i]);
            }
            trimmedWords.push_back(temp);
        }
        for (auto w : trimmedWords)
        {
            cout << w << " \n";
        }
        return trimmedWords;
    }
};
int main()
{
    string s = "catsanddog";
    vector<string> wordDict = {"cat",
                               "cats",
                               "and",
                               "sand",
                               "dog"};
    vector<string> words;
    Solution1 A;
    words = A.wordBreak(s, wordDict);
}