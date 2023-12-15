#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string minR(string str)
{
    string min = str;

    for (int i = 0; i < str.length(); i++)
    {
        rotate(str.begin(), str.begin() + 1, str.end());
        if (str.compare(min) < 0)
        {
            min = str;
        }
    }
    return min;
}
// Time complexity = O(nlogn)
int main()
{
    string str;
    cin >> str;
    cout << minR(str) << endl;
    return 0;
}
