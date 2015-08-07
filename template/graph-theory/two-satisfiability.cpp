const int N = ;

int n, times, comps, top;
vector<int> adj[N];
int dfn[N], low[N], comp[N], stack[N];

void add(int x, int a, int y, int b) {
	adj[x << 1 | a].push_back(y << 1 | b);
}

void tarjan(int x) {
	dfn[x] = low[x] = ++times;
	stack[top++] = x;
	for (int i = 0; i < (int)adj[x].size(); ++i) {
		int y = adj[x][i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (!comp[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (low[x] == dfn[x]) {
		comps++;
		do {
			int y = stack[--top];
			comp[y] = comps;
		} while (stack[top] != x);
	}
}

bool solve() {
	times = top = comps = 0;
	fill(dfn + 1, dfn + (n << 1 | 1) + 1, 0);
	fill(comp + 1, comp + (n << 1 | 1) + 1, 0);
	for (int i = 2; i <= (n << 1 | 1); ++i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (comp[i << 1] == comp[i << 1 | 1]) {
			return false;
		}
		ans[i] = (comp[i << 1 | 1] < comp[i << 1]);
	}
	return true;
}

void clear() {
	for (int i = 2; i <= (n << 1 | 1); ++i) {
		adj[i].clear();
	}
}