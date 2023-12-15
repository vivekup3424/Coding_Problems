// Aditya Verma
// Given a string you need to print all possible strings that can be made by
// placing spaces (zero or one) in between them. Output should be printed in
// sorted increasing order of strings.
//
// Input:  str[] = "ABC"
// Output: (A B C)(A BC)(AB C)(ABC) .

#include <bits/stdc++.h>
using namespace std;
vector<string> permutations;
vector<string> AllPermutations(string perm, int i, string s)
{
    if (i == s.size())
    {
        permutations.push_back(perm);
    }
    perm.push_back(s[i]);
    perm.push_back(' ');
    AllPermutations(perm, i + 1, s);
    perm.pop_back();
    AllPermutations(perm, i + 1, s);
}
int main()
{
    string s = "ABC";
    string empty = "";
    AllPermutations(empty, 0, s);
    for (auto perm : permutations)
    {
        cout << perm << endl;
    }
    return 0;
}