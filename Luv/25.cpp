// Everything about C++ STL MAPS - Part 1
//| Competitive Programming Course | Episode 2

#include <bits/stdc++.h>
using namespace std;

int main()
{
    // normal maps are implemented using red-black tree
    map<int, string> m;
    m[1] = "abc";
    m[5] = "cdc";
    m[3] = "acd";
    m.insert({4, "fgh"}); // O(logn)
    map<int, string>::iterator it;
    for (it = m.begin(); it != m.end(); it++)
    {
        cout << (*it).first << " " << it->second << "\n";
    }

    for (auto &pr : m) // short-cut code with auto-based iterator
    {
        cout << pr.first << " " << pr.second << "\n";
    }
    return 0;
    // insertion and access in map has O(logn) for both
}

// find and erase
int main2()
{
    map<int, string> m;
    // returns an iterator
    auto it = m.find(3);
    if (it == m.end())
        cout << "no value\n";

    // key-value
    m.erase(3); // O{logn}
    return 0;
}

// Q.
// Given N strings,
// print unique strings in lexographical order
// with their frequency