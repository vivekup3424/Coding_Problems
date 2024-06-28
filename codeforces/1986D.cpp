#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        char s[n];
        for (int i = 0; i < n; i++)
        {
            cin >> s[i];
        }
        if (n < 3)
        {
            cout << atoi(s) << endl;
        }
        else
        {
            // check if it contains Zero
            bool containsZero = false;
            for (auto i : s)
            {
                if (i == '0')
                {
                    containsZero = true;
                    break;
                }
            }
            if (containsZero == true)
            {
                cout << "0\n";
            }
            else
            {
                // take two digits as numeral,and other non-one numbers
                int mini = 0;
                for (int i = 0; i < n - 1; i++)
                {
                    int current_sum = 0;
                    int numeral = (s[i] - '0') * 10 + (s[i + 1] - '0');
                    current_sum += numeral;
                    for (int j = i + 3; j < n; j++)
                    {
                        if (s[j] != '1')
                        {
                            current_sum += (s[j] - '0');
                        }
                    }
                    mini = min(current_sum, mini);
                }
                cout << mini << endl;
            }
        }
    }
    return 0;
}
