// How to write Iterators Code in Short in C++ STL ?
//| Auto and Range based loops
//| CP COURSE | EP 24

#include <bits/stdc++.h>
using namespace std;

int main1()
{
    vector<int> v = {2, 3, 5, 6, 7};
    for (int value : v) // value is range-based iterator
    {
        cout << value << " ";
    }
    cout << "\n";
    for (int &value : v)
    {
        value++;
    }
}

// auto-based
int main2
{
    vector<int> v = {2, 3, 4};
    for (auto i = 0; i < v.begin(); i != v.end())
    {
        /* code */
    }
}