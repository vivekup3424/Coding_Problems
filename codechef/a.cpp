#include <iostream>
#include <vector>
using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
    {
        int N;
        cin >> N;
        vector<int> P(N);
        for (int i = 0; i < N; cin >> P[i++])
            ;
        auto count = [&](vector<int> &P)
        {
            int c = 0, l = 1, n = P.size();
            for (int i = 1; i < n; ++i)
                P[i] > P[i - 1] ? ++l : (c += l * (l + 1) / 2, l = 1);
            return c + l * (l + 1) / 2;
        };
        int mx = count(P);
        for (int i = 0; i < N - 1; ++i)
            for (int j = i + 1; j < N; ++j)
                swap(P[i], P[j]), mx = max(mx, count(P)), swap(P[i], P[j]);
        cout << mx << "\n";
    }
    return 0;
}
