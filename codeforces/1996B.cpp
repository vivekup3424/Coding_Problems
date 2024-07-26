#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // To ignore the newline character after reading the integer t

    while (t--)
    {
        int n, k;
        cin >> n >> k;
        cin.ignore(); // To ignore the newline character after reading n and k

        vector<string> mat(n);
        for (int i = 0; i < n; i++)
        {
            getline(cin, mat[i]);
        }

        int reducedSize = n / k;
        vector<string> ans(reducedSize, string(reducedSize, '0'));

        for (int i = 0; i < reducedSize; i++)
        {
            for (int j = 0; j < reducedSize; j++)
            {
                // All cells in the block are guaranteed to be the same.
                if (mat[i * k][j * k] == '0')
                {
                    ans[i][j] = '0';
                }
                else
                {
                    ans[i][j] = '1';
                }
            }
        }

        for (const string &row : ans)
        {
            cout << row << endl;
        }
    }

    return 0;
}
