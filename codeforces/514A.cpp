#include <bits/stdc++.h>
using namespace std;
int main(int argc, char const *argv[])
{
    string temp = "";
    cin >> temp;
    for (int i = 0; i < temp.size(); i++)
    {
        if (i == 0 && temp[i] == '9')
        {
            continue;
        }
        if (temp[i] >= '5')
        {
            temp[i] = '9' - temp[i] + '0';
        }
    }
    cout << temp << endl;
    return 0;
}
