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
        
        long long ans = 0;
        vector<int> first_occurence(26, -1);
        for (int i = 0; i < n; i++) {
            char c = s[i] - 'a';
            if(first_occurence[c]==-1){
                first_occurence[c] = i;
                ans += (n-i);
            }
            else{
                continue;
            }
        }
        cout << ans << endl;
    }
    return 0;
}