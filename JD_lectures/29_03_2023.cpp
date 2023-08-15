
#include <bits/stdc++.h>
using namespace std;
const int ALPHABET_CONSTANTS = 26;
struct TrieNode
{
    struct TrieNode *children[ALPHABET_CONSTANTS];
    bool isEndOfWord;
};

// polynomial hashing
// The idea is to construct
// an array h such that h[k] contains the hash value
// h[k] contains the hash-value o
// h[0] = s[0]
// h[k] = (h[k-1]A+s[k])modB