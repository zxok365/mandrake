const int N = ;

int n, m, times;
vector<int> adj[N];
int matchx[N], matchy[N];
int visit[N];

void add(int x, int y) {
	adj[x].push_back(y);
}

bool dfs(int x) {
	for (int i = 0; i < (int)adj[x].size(); ++i) {
		int y = adj[x][i];
		if (visit[y] != times) {
			visit[y] = times;
			if (!matchy[y] || dfs(matchy[y])) {
				matchy[y] = x;
				return true;
			}
		}
	}
	return false;
}

int solve() {
	fill(matchy + 1, matchy + m + 1, 0);
	int ans = 0;
	for (int i = 1; i <= n; ++i) {
		times++;
		ans += dfs(i);
	}
	for (int i = 1; i <= m; ++i) {
		matchx[matchy[i]] = i;
	}
	return ans;
}

void clear() {
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
	}
}