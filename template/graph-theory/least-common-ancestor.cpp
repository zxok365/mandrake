const int N = , M = ;

int n;
vector<int> adj[N];
int height[N];
int parent[N][M];

void add(int x, int y) {
	adj[x].push_back(y);
	adj[y].push_back(x);
}

int lca(int x, int y) {
	if (height[x] < height[y]) {
		swap(x, y);
	}
	for (int i = 0; i < M; ++i) {
		if (height[x] - height[y] >> i & 1) {
			x = parent[x][i];
		}
	}
	if (x == y) {
		return x;
	}
	for (int i = M - 1; i >= 0; --i) {
		if (parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}
	}
	return parent[x][0];
}

void build(int root) {
	vector<int> queue;
	fill(height + 1, height + n + 1, -1);
	queue.push_back(root);
	height[root] = 0;
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)adj[x].size(); ++i) {
			int y = adj[x][i];
			if (height[y] == -1) {
				height[y] = height[x] + 1;
				parent[y][0] = x;
				queue.push_back(y);
			}
		}
	}
	for (int j = 1; j < M; ++j) {
		for (int i = 1; i <= n; ++i) {
			parent[i][j] = parent[parent[i][j - 1]][j - 1];
		}
	}
}

void clear(int n) {
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
	}
}