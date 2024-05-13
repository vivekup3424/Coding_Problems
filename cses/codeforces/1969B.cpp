#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    int t;
    cin >> t;
    cin.ignore(); // to clear the newline character after reading t

    while (t--)
    {
        string s;
        getline(cin, s);

        vector<int> nums;
        for (char c : s)
        {
            nums.push_back(c - '0');
        }

        int zeroes = 0;
        for (int num : nums)
        {
            if (num == 0)
            {
                zeroes++;
            }
        }

        vector<int> cnt(2, 0);
        long long ans = 0;
        for (int c : nums)
        {
            cnt[c]++;
            if (c == 0)
            {
                ans += (cnt[1] > 0 ? 1 : 0);
            }
            else
            {
                ans += (zeroes - cnt[0]);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
