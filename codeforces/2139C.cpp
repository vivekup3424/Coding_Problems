#include <bits/stdc++.h>
using namespace std;

struct State {
	long long chocola, vanilla;
	vector<int> ops;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	cerr << "t=" << t << endl;
	while (t--) {
		long long k, x;
		cin >> k >> x;
		cerr << "Testcase: k=" << k << ", x=" << x << endl;
		long long chocola = pow(2,k), vanilla = pow(2,k);
		long long target_chocola = x, target_vanilla = chocola + vanilla - x;

		cerr << "Initial: chocola=" << chocola << ", vanilla=" << vanilla << ", target_chocola=" << target_chocola << ", target_vanilla=" << target_vanilla << endl;

		if (chocola == target_chocola && vanilla == target_vanilla) {
			cout << "0\n";
            cout<<endl;
			cerr << "Already at target\n";
			continue;
		}

		queue<State> q;
		set<pair<long long, long long>> visited;
		q.push({chocola, vanilla, {}});
		visited.insert({chocola, vanilla});
		bool found = false;
		int bfs_steps = 0;
		while (!q.empty()) {
			State cur = q.front(); q.pop();
			bfs_steps++;
			cerr << "BFS step " << bfs_steps << ": chocola=" << cur.chocola << ", vanilla=" << cur.vanilla << ", ops=" << cur.ops.size() << endl;
			if (cur.chocola == target_chocola && cur.vanilla == target_vanilla) {
				cout << cur.ops.size() << '\n';
				for (int i = 0; i < cur.ops.size(); ++i) cout << cur.ops[i] << " ";
				if (!cur.ops.empty()) cout << '\n';
				cerr << "Found solution in " << cur.ops.size() << " steps\n";
				found = true;
				break;
			}
			if (cur.chocola % 2 == 0) {
				long long na = cur.chocola / 2, nb = cur.vanilla + cur.chocola / 2;
				if (!visited.count({na, nb})) {
					vector<int> nops = cur.ops; nops.push_back(1);
					q.push({na, nb, nops});
					visited.insert({na, nb});
					cerr << "  Operation 1: chocola=" << na << ", vanilla=" << nb << endl;
				}
			}
			if (cur.vanilla % 2 == 0) {
				long long na = cur.chocola + cur.vanilla / 2, nb = cur.vanilla / 2;
				if (!visited.count({na, nb})) {
					vector<int> nops = cur.ops; nops.push_back(2);
					q.push({na, nb, nops});
					visited.insert({na, nb});
					cerr << "  Operation 2: chocola=" << na << ", vanilla=" << nb << endl;
				}
			}
		}
		if (!found) cerr << "No solution found for k=" << k << ", x=" << x << endl;
	}
	return 0;
}
