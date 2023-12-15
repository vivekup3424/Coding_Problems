#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    // FNV-1a hash function
    uint32_t hashFnv1a(const std::string &str)
    {
        const uint32_t FNV_PRIME = 16777619;
        const uint32_t FNV_OFFSET_BASIS = 2166136261;

        uint32_t hash = FNV_OFFSET_BASIS;

        for (char c : str)
        {
            hash ^= c;
            hash *= FNV_PRIME;
        }

        return hash;
    }
    unordered_map<string, string> shortLong;

    // Encodes a URL to a shortened URL.
    string encode(string longUrl)
    {
        int n = hashFnv1a(longUrl);
        string key = to_string(n);
        shortLong.insert({key, longUrl});
        return key;
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl)
    {
        return shortLong[shortUrl];
    }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));
int main()
{
}