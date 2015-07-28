#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 222222;

int n, m;
vector<int> adj[N];
int height[N], parent[N], dist[N], dp[N];
int father[N][20];
vector<pair<pair<int, int>, int> > chain[N];

int jump(int x, int k) {
	for (int i = 0; i < 20; ++i) {
		if (k >> i & 1) {
			x = father[x][i];
		}
	}
	return x;
}

int lca(int x, int y) {
	if (height[x] < height[y]) {
		swap(x, y);
	}
	x = jump(x, height[x] - height[y]);
	if (x == y) {
		return x;
	}
	for (int i = 19; i >= 0; --i) {
		if (father[x][i] != father[y][i]) {
			x = father[x][i];
			y = father[y][i];
		}
	}
	return father[x][0];
}

int find(int x) {
	if (parent[x] != x) {
		int root = find(parent[x]);
		dist[x] += dist[parent[x]];
		return parent[x] = root;
	} else {
		return x;
	}
}

void mergy(int x, int y, int w) {
	x = find(x);
	y = find(y);
	parent[x] = y;
	dist[x] = w;
}

void solve(void) {
	scanf("%d%d", &n, &m);

	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
		chain[i].clear();
	}	
	
	for (int i = 1; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	vector<int> queue;
	height[1] = 0;
	father[1][0] = 0;
	queue.push_back(1);
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)adj[x].size(); ++i) {
			int y = adj[x][i];
			if (y == father[x][0]) {
				continue;
			}
			height[y] = height[x] + 1;
			father[y][0] = x;
			queue.push_back(y);
		}
	}
	
	for (int j = 1; j < 20; ++j) {
		for (int i = 1; i <= n; ++i) {
			father[i][j] = father[father[i][j - 1]][j - 1];
		}
	}
	
	for (int i = 1; i <= m; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		chain[lca(x, y)].push_back(make_pair(make_pair(x, y), w));
	}
	
	for (int i = 1; i <= n; ++i) {
		parent[i] = i;
		dist[i] = 0;
	}
	
	for (int head = n - 1; head >= 0; --head) {
		int x = queue[head];
		int sum = 0;
		for (int i = 0; i < (int)adj[x].size(); ++i) {
			int y = adj[x][i];
			if (y == father[x][0]) {
				continue;
			}
			sum += dp[y];
		}
		dp[x] = sum;
		for (int i = 0; i < (int)chain[x].size(); ++i) {
			int a = chain[x][i].first.first;
			int b = chain[x][i].first.second;

			int son1 = jump(a, height[a] - height[x] - 1);
			int son2 = jump(b, height[b] - height[x] - 1);
			
			find(a);
			find(b);

			dp[x] = max(dp[x], chain[x][i].second + sum + dist[a] + dist[b]);
		}
		mergy(x, father[x][0], sum - dp[x]);
	}
	printf("%d\n", dp[1]);
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
