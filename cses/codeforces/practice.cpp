#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<long long> vll;
typedef vector<vector<long long>> vvll;

inline void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

// Template function to input elements to a vector
template <typename T>
void inputVector(vector<T> &v, int n) {
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
}

// Template function to output elements of a vector
template <typename T>
void outputVector(const vector<T> &v, int n) {
    for (int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << "\n";
}

int main() {
    fast_io();
    ll T;
    cin >> T;
    while (T--) {
        ll n, k;
        cin >> n >> k;
        vvll graph(n);
        vector<pair<int,int>> edges;
        for (ll i = 0; i < n; i++) {
            ll a, b;
            cin >> a >> b;
            a--;
            b--;
            edges.push_back({a, b});
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        // degrees array
        vll degrees(n, 0);
        for (int i = 0; i < n; i++) {
            degrees[i] = graph[i].size();
        }
        priority_queue<pair<ll,ll>> maxHeap; // Changed comparator
        // stores edge index and corresponding min vertex degree
        for (int i = 0; i < edges.size(); i++) {
            ll a = edges[i].first, b = edges[i].second;
            ll min_degree = min(degrees[a], degrees[b]); // Corrected typo
            maxHeap.push({min_degree, i}); // Changed order
        }
        while(k--){
            //remove the top edge index
            ll edge_index = maxHeap.top().first;
            maxHeap.pop();
            ll vertex_1 = edges[edge_index].first;
            ll vertex_2 = edges[edge_index].second;
            //reduce the degrees
            degrees[vertex_1]--;
            degrees[vertex_2]--;
            //remove the connected nodes from the graph
            graph[vertex_1].erase(find(graph[vertex_1].begin(), graph[vertex_1].end(), vertex_2));
            graph[vertex_2].erase(find(graph[vertex_2].begin(), graph[vertex_2].end(), vertex_1));2
        }
    }
}
