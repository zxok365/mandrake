#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

const int N = 111111;
const int inf = 1 << 29;
using namespace std;
struct Edge {
	int to, nxt, c;
}nod[N * 2];
int tot = -1;
int head[N], dist[N], cur[N], po[N][2], S, T; 
int n, m, s1, s2, t1, t2;
void add(int x, int y) {
	nod[++tot].to = y;
	nod[tot].nxt = head[x];
	head[x] = tot;
	nod[tot].c = 1;
	
	nod[++tot].to = x;
	nod[tot].nxt = head[y];
	head[y] = tot;
	nod[tot].c = 0;
}
bool bfs() {
	for (int i = 1; i <= T; i++) dist[i] = -1;
	queue<int> que;
	que.push(S);
	dist[S] = 0;
	for (; !que.empty(); que.pop()) {
		int t = que.front();
		for (int p = head[t]; p > -1; p = nod[p].nxt) {
			if (dist[nod[p].to] == -1 && nod[p].c) {
				dist[nod[p].to] = dist[t] + 1;
				que.push(nod[p].to);
			}
		}
	}
	return dist[T] > -1;
}

int dfs(int u, int ext) {
	if (u == T) return ext;
	else {
		int ret = 0, p = cur[u];
		for (p; p > -1; p = nod[p].nxt, cur[u] = p) {
			if (nod[p].c && dist[nod[p].to] == dist[u] + 1) {
				int flow = dfs(nod[p].to, min(ext, nod[p].c));
				nod[p].c -= flow;
				nod[p ^ 1].c += flow;
				ret += flow;
				ext -= flow;
			}
			if (ext == 0) break;
		}
		if (ext == 0) dist[u] = -1;
		return ret;
	}
}


vector<int> ans;
void go(int x) {
 	if (x <= n) ans.push_back(x);
	for (int p = head[x]; p > -1; p = nod[p].nxt) {
		if (p % 2 == 0 && nod[p].c == 0) {
			go(nod[p].to);
		}
	}
}

void print_ans() {
	go(s1);
	for (int i = 0; i < (int) ans.size(); i++) {
		printf("%d%c", ans[i], (i == ans.size() - 1) ? '\n' : ' ');
	}
	ans.clear();
	go(s2);
	for (int i = 0; i < (int) ans.size(); i++) {
		printf("%d%c", ans[i], (i == ans.size() - 1) ? '\n' : ' ');
	}
}
void Dinic() {
	int flow = 0;
	while (bfs()) {
		for (int i = 1;  i <= T; i++) cur[i] = head[i];
		flow += dfs(S, inf);
	}
	if (flow < 2) {
		puts("NO");
		return;
	}

	puts("YES");
	print_ans();
}
int main () {
	scanf("%d%d", &n, &m);
	scanf("%d%d%d%d", &s1, &t1, &s2, &t2);
	if (s1 > t1) swap(s1, t1);
	if (s2 > t2) swap(s2, t2);
	for (int i = 1; i <= n; i++) {
		po[i][0] = i;
		po[i][1] = i + n;
	}
	tot = -1;
	
	for (int i = 1; i <= 2 * n + 2; i++) head[i] = -1;
	
	for (int i = 1; i <= n; i++) {
		add(po[i][0], po[i][1]);
	}
	for (int i = 1; i <= m; i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u > v) swap(u, v);
		add(po[u][1], po[v][0]);
		add(po[v][1], po[u][0]);
	}
	
	S = 2 * n + 1;
	T = 2 * n + 2;
	
	add(S, po[s1][0]);
	add(po[t1][1], T);
	add(S, po[s2][0]);
	add(po[t2][1], T);
	Dinic();
	
	return 0;
}
