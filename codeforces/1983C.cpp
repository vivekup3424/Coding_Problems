#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> a(n), b(n), c(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
        
        // Calculate total value
        ll total = accumulate(a.begin(), a.end(), 0LL);
        
        // Calculate minValueRequired
        ll minValueRequired = (total + 2) / 3;
        
        // Prefix sums
        vector<ll> prefixA(n), prefixB(n), prefixC(n);
        prefixA[0] = a[0];
        prefixB[0] = b[0];
        prefixC[0] = c[0];
        
        for (int i = 1; i < n; i++) {
            prefixA[i] = prefixA[i - 1] + a[i];
            prefixB[i] = prefixB[i - 1] + b[i];
            prefixC[i] = prefixC[i - 1] + c[i];
        }
        
        // Suffix sums
        vector<ll> suffixA(n), suffixB(n), suffixC(n);
        suffixA[n - 1] = a[n - 1];
        suffixB[n - 1] = b[n - 1];
        suffixC[n - 1] = c[n - 1];
        
        for (int i = n - 2; i >= 0; i--) {
            suffixA[i] = suffixA[i + 1] + a[i];
            suffixB[i] = suffixB[i + 1] + b[i];
            suffixC[i] = suffixC[i + 1] + c[i];
        }
        
        // Find valid partition
        int l = -1, r = n;
        
        // Finding l
        for (int i = 0; i < n; i++) {
            if (prefixA[i] >= minValueRequired || prefixB[i] >= minValueRequired || prefixC[i] >= minValueRequired) {
                l = i;
                break;
            }
        }
        
        // Finding r
        for (int i = n - 1; i > l; i--) {
            if (suffixA[i] >= minValueRequired || suffixB[i] >= minValueRequired || suffixC[i] >= minValueRequired) {
                r = i + 1;
                break;
            }
        }
        
        // Check if valid partition found
        if (l == -1 || r == n || r <= l + 1) {
            cout << "-1\n";
        } else {
            // Check for non-overlapping subarrays
            bool valid = true;
            for (int i = l + 1; i < r; i++) {
                if ((prefixA[i] >= minValueRequired || prefixB[i] >= minValueRequired || prefixC[i] >= minValueRequired) &&
                    (suffixA[i] >= minValueRequired || suffixB[i] >= minValueRequired || suffixC[i] >= minValueRequired)) {
                    valid = false;
                    break;
                }
            }
            
            if (!valid) {
                cout << "-1\n";
            } else {
                // Output the indices
                int la = l + 1;
                int ra = r;
                
                // Find lb and rb
                int lb = -1, rb = n;
                for (int i = la; i < ra; i++) {
                    if (prefixA[i] >= minValueRequired) {
                        lb = i + 1;
                        break;
                    } else if (prefixB[i] >= minValueRequired) {
                        lb = i + 1;
                        break;
                    } else if (prefixC[i] >= minValueRequired) {
                        lb = i + 1;
                        break;
                    }
                }
                
                for (int i = ra - 1; i > la; i--) {
                    if (suffixA[i] >= minValueRequired) {
                        rb = i;
                        break;
                    } else if (suffixB[i] >= minValueRequired) {
                        rb = i;
                        break;
                    } else if (suffixC[i] >= minValueRequired) {
                        rb = i;
                        break;
                    }
                }
                
                // Find lc and rc
                int lc = -1, rc = n;
                for (int i = ra; i < n; i++) {
                    if (prefixA[i] >= minValueRequired || prefixB[i] >= minValueRequired || prefixC[i] >= minValueRequired) {
                        lc = i + 1;
                        break;
                    }
                }
                
                for (int i = n - 1; i >= ra; i--) {
                    if (suffixA[i] >= minValueRequired || suffixB[i] >= minValueRequired || suffixC[i] >= minValueRequired) {
                        rc = i + 1;
                        break;
                    }
                }
                
                cout << la << " " << ra << " " << lb << " " << rb << " " << lc << " " << rc << "\n";
            }
        }
    }
    
    return 0;
}
