// Pairs and Vectors: C++ STL Tutorial for Beginner

#include <bits/stdc++.h>
using namespace std;

int main()
{
    pair<int, string> p;
    p = make_pair(2, "abc");
    cout << p.first << " " << p.second << "\n";
    pair<int, string> *p1;
    p1 = &p;
    p1->first = 8;
    pair<int, int> p_array[3];
    p_array[0] = {1, 3};
    p_array[1] = {3, 4};
    p_array[2] = {7, 7};
    swap(p_array[0], p_array[2]);
    for (int i = 0; i < 3; i++)
    {
        cout << p_array[i].first << " " << p_array[i].second << "\n";
    }
}