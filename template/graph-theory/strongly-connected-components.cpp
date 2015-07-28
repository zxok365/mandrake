namespace strongly_connected_components {

const int N = ;

int n, times, comps, top;
int dfn[N], low[N], comp[N], stack[N];

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

void solve() {
	times = comps = top = 0;
	fill(dfn + 1, dfn + n + 1, 0);
	fill(comp + 1, comp + n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
}

void clear() {
	for (int i = 1; i <= n; ++i) {
		adj[i].clear();
	}
}

}
