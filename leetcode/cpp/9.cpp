
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    bool isPalindrome(int x)
    {
        string a = to_string(x);
        int i = 0, j = a.size() - 1;
        while (i <= j)
        {
            if (a[i] != a[j])
                return false;
            i++;
            j--;
        }
        return true;
    }
};
int main()
{
}