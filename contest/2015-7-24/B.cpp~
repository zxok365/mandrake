#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 111111;

int n;
vector<pair<int, int> > adj[N];

int dfs(int x, int from, int weight) {
	bool leaf = true;
	int ret = 0, sum = weight, maximum = weight;
	for (int i = 0; i < (int)adj[x].size(); ++i) {
		int y = adj[x][i].first;
		if (y == from) {
			continue;
		}
		ret += dfs(y, x, adj[x][i].second);
		sum += adj[x][i].second;
		maximum = max(maximum, adj[x][i].second);
		leaf = false;
	}
	if (!leaf) {
		ret -= weight;
		if (maximum > sum - maximum) {
			ret += maximum;
		} else {
			ret += (sum + 1) >> 1;
		}
	}
	return ret;
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
	}
	for (int i = 1; i <= n - 1; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		adj[x].push_back(make_pair(y, w));
		adj[y].push_back(make_pair(x, w));
	}
	printf("%d\n", dfs(1, 0, 0));
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}
