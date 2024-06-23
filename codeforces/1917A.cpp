#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int N = 105;

int t, n;
int a[N];

int main() {
    cin >> t;
    
    while (t--) {
        cin >> n;
        
        int c_neg = 0;
        int c_zero = 0;
        int c_pos = 0;
        
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            
            if (a[i] < 0) {
                c_neg++;
            } else if (a[i] == 0) {
                c_zero++;
            } else {
                c_pos++;
            }
        }
        
        if (c_zero || c_neg % 2) {
            cout << 0 << endl;
        } else {
            cout << 1 << endl;
            cout << 1 << " " << 0 << endl;
        }
    }
    return 0;
}