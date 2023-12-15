// Shortest Common SuperSequence (SCS)
//     Given two strings str1 and str2,
//     find the shortest string that has both str1 and str2 as subsequences.Examples :
//
//     Input : str1 = "geek",
//             str2 = "eke" Output : "geeke"
#include <bits/stdc++.h>
using namespace std;

int length_SCS(string x, string y, int a, int b)
{
    if (a == 0 and b == 0)
        return 0;
    else if (a == 0)
        return b;
    else if (b == 0)
        return a;
    else if (x[a - 1] == y[b - 1])
        return 1 + length_SCS(x, y, a - 1, b - 1);
    else
    {
        return 1 + min(length_SCS(x, y, a, b - 1), length_SCS(x, y, a - 1, b));
    }
}
// or you can do it by other method that we first find the LCS and then solve the problem
int main()
{
    string str1 = "geek";
    int a = str1.size();
    string str2 = "eke";
    int b = str2.size();
    int SCS = length_SCS(str1, str2, a, b);
    cout << SCS << "\n";
    return 0;
}