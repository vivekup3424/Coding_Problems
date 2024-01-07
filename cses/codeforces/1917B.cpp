#include <iostream>
#include <vector>
#include <string>

using namespace std;

int n, t;

int main() {
    cin >> t;
    
    while (t--) {
        cin >> n;
        string s;
        cin >> s;
        
        vector<long long> ans(n, 0);
        vector<int> nxt(26, n);
        ans[n - 1] = 1;
        nxt[s[n - 1] - 'a'] = n - 1;
    
        for (int i = n - 2; i >= 0; i--) {
            ans[i] = ans[i + 1] + (nxt[s[i] - 'a'] - i);
            nxt[s[i] - 'a'] = i;
        }
    
        cout << ans[0] << endl;
    }
    return 0;
}