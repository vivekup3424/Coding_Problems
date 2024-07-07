#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

bool can_transform(vector<vector<int>>& a, vector<vector<int>>& b, int n, int m) {
    // Compute the difference matrix
    vector<vector<int>> diff(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            diff[i][j] = (a[i][j] - b[i][j] + 3) % 3;
        }
    }
    
    // Check if all values in the diff matrix can be transformed to zero
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            // If top-left corner is non-zero, apply operation to make it zero
            if (diff[i][j] != 0) {
                int change = (3 - diff[i][j]) % 3;
                diff[i][j] = (diff[i][j] + change) % 3;
                diff[i][j + 1] = (diff[i][j + 1] + 2 * change) % 3;
                diff[i + 1][j] = (diff[i + 1][j] + 2 * change) % 3;
                diff[i + 1][j + 1] = (diff[i + 1][j + 1] + change) % 3;
            }
        }
    }

    // Check if the last row and column are all zeros
    for (int i = 0; i < n; ++i) {
        if (diff[i][m - 1] != 0) return false;
    }
    for (int j = 0; j < m; ++j) {
        if (diff[n - 1][j] != 0) return false;
    }

    return true;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        vector<vector<int>> b(n, vector<int>(m));
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char x;
                cin >> x;
                a[i][j] = x - '0';
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                char x;
                cin >> x;
                b[i][j] = x - '0';
            }
        }

        if (can_transform(a, b, n, m)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
