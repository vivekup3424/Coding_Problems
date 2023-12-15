
#include <bits/stdc++.h>
using namespace std;

int main()
{
    string A;
    cin >> A;
    char element = 'I';
    int length = 0;
    for (char c : A)
    {
        if (c != element)
        {
            element = c;
            length = 1;
        }
        else
        {
            length++;
            if (length >= 7)
            {
                cout << "YES" << endl;
                return 0;
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}