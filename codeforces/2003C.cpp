#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))
using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 1000100;

int n;
pii a[99];
char s[maxn];

void solve() {
	scanf("%d%s", &n, s + 1);
	for (int i = 0; i < 26; ++i) {
		a[i] = mkp(0, i);
	}
	for (int i = 1; i <= n; ++i) {
		++a[s[i] - 'a'].fst;
	}
	sort(a, a + 26, greater<pii>());
	queue<pii> q;
	while (a[0].fst > a[1].fst) {
		putchar('a' + a[0].scd);
		--a[0].fst;
	}
	for (int i = 0; i < 26; ++i) {
		q.push(a[i]);
	}
	while (q.size()) {
		pii p = q.front();
		q.pop();
		if (!p.fst) {
			continue;
		}
		putchar('a' + p.scd);
		--p.fst;
		q.push(p);
	}
	putchar('\n');
}

int main() {
	int T = 1;
	scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}
