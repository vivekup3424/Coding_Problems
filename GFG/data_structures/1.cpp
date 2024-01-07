#include <bits/stdc++.h>
using namespace std;

const int N = 1e4+1;

int fen[N];
void update(int i, int add){
    while(i < N){
        fen[i] += add;
        i = (i+(i&-i));
    }
}
int sum(int i){
    int s = 0;
    while(i > 0){
        s += fen[i];
        i = i - (i & -i);
    }
    return s;
}

//template below
template <class T>
struct BIT { //1-indexed
  int n; vector<T> t;
  BIT() {}
  BIT(int _n) {
    n = _n; t.assign(n + 1, 0);
  }
  T query(int i) {
    T ans = 0;
    for (; i >= 1; i -= (i & -i)) ans += t[i];
    return ans;
  }
  void upd(int i, T val) {
    if (i <= 0) return;
    for (; i <= n; i += (i & -i)) t[i] += val;
  }
  void upd(int l, int r, T val) {
    upd(l, val);
    upd(r + 1, -val);
  }
  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
};