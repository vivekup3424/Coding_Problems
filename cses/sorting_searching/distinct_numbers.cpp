
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    set<long long int> s;
    while (n--)
    {
        long long int temp;
        cin >> temp;
        s.insert(temp);
    }
    cout << s.size() << endl;
}