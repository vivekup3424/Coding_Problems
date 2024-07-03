#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(int argc, char const *argv[])
{
    int t;
    cin >> t;
    while (t--)
    {
        int num_branches, base, height;
        cin >> num_branches >> base >> height;
        vector<int> base_oordinate(num_branches);
        for (int i = 0; i < num_branches; i++)
        {
            cin >> base_oordinate[i];
        }
        sort(base_oordinate.begin(), base_oordinate.end());
        ll area = 0;
        for (int i = 0; i < num_branches; i++)
        {
            if (i == num_branches - 1)
            {
                area += (height * base) >> 1;
            }
            else if (base_oordinate[i + 1] - base_oordinate[i] >= height)
            {
                area += (height * base) >> 1;
            }
            else
            {
                int diff = base_oordinate[i + 1] - base_oordinate[i];
                area += (diff * height) >> 1;
            }
        }
        cout << area << endl;
    }
    return 0;
}
