#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        sort(a.begin(), a.end(), greater<int>());
        
        long long answer = 0;
        int ovensToVisit = min(n, m);
        
        for (int i = 0; i < ovensToVisit; ++i) {
            answer += (long long)a[i] * (m - i);
        }
        cout << answer << endl;
    }
    return 0;
}
