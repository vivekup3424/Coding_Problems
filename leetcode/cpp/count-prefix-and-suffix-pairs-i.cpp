#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isPrefixAndSuffix(string word1, string word2){
        if (word2.length() < word1.length())
        {
            return false;
        }
        for(int i = 0; i < word1.length(); i++){
            if(word1[i]!=word2[i]){
                return false;
            }
        }
        for(int i = 0; i < word1.length(); i++){
            if(word1[i]!=word2[word2.length()-word1.length()+i]){
                return false;
            }
        }
        return true;
    }
    int countPrefixSuffixPairs(vector<string>& words) {
        int count = 0;
        for(int i = 0; i < words.size(); i++){
            for(int j = i+1; j < words.size(); j++){
                if(isPrefixAndSuffix(words[i],words[j])){
                    cout<<i<<"=>"<<j<<endl;
                    count++;
                }
            }
        }
        return count;
    }
};

//More Efficient Solution
class Solution {
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        int length = words.size();
        
        int numPairs = 0;
        for (int i = 0; i < length; ++i) {
            for (int j = i + 1; j < length; ++j)
                numPairs += isPrefixSuffix(words[i], words[j]);
        }

        return numPairs;        
    }

    bool isPrefixSuffix(string word1, string word2) {
        int length1 = word1.length(), length2 = word2.length();

        if (length1 > length2)
            return false;

        bool flag = true;
        for (int l1 = 0, r1 = length1 - 1, l2 = 0, r2 = length2 - 1; l1 < length1 && r1 >= 0 && l2 < length2 && r2 >= 0 && flag; ++l1, --r1, ++l2, --r2)
            flag = (word1[l1] == word2[l2]) && (word1[r1] == word2[r2]);
        
        return flag;
    }
};