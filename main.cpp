#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;

using ll = long long;
using vb = vector<bool>;
using vvb = vector<vb>;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<ll>;
using vvl = vector<vl>;
using pii = pair<int, int>;
using vii = vector<pii>;
using pll = pair<ll, ll>;
using vll = vector<pll>;
using Edges = vector<tuple<ll, ll, ll>>;

ll n, m;
Edges edges;
vl par;
int added;
ll ans;

ll getRoot(const ll x) {
	if (x == par[x]) {
		return x;
	}

	return par[x] = getRoot(par[x]);
}

void updateRoot(const ll x, const ll y) {
	const auto rx = getRoot(x);
	const auto ry = getRoot(y);

	par[rx] = par[ry];
}

void solve() {
	added = 0;
	ans = 0;

	for (const auto& [c, x, y] : edges) {
		const auto rx = getRoot(x);
		const auto ry = getRoot(y);

		if (rx == ry) {
			continue;
		}

		++added;
		if (added < n - 1) {
			ans += c;
		}

		updateRoot(x, y);

		if (n - 1 == added) {
			break;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	cin >> n >> m;

	par = vl(n + 1);
	for (auto i = 0; i < n; ++i) {
		par[i] = i;
	}

	edges = Edges{};
	edges.reserve(m);
	while (0 < (m--)) {
		int a, b, c;
		cin >> a >> b >> c;
		edges.push_back({ c, a, b });
	}

	sort(edges.begin(), edges.end());

	solve();
	cout << ans;

	return 0;
}