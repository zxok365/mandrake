#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <climits>
using namespace std;
const int N = 6666;
const int M = 222222;
const int inf = INT_MAX / 2;
struct Node{
	int to,nxt,w;
}nod[M*2];
struct Node2{
	int to,nxt,c;
}nod2[M*2];
struct Edge{
	int u, v, w;
}e[M];
int S, T;
int q[N * 50], head[N], head2[N], w[N], d[N], inq[N], finish[N];
int ans1 , ans2;
int n,m,tot;
void add1(int u, int v, int ww){
	nod[++tot].nxt = head[u];
	head[u] = tot;
	nod[tot].to = v;
	nod[tot].w = ww;
}

void add2(int u ,int v, int c) {
	nod2[++tot].nxt = head2[u];
	head2[u] = tot;
	nod2[tot].to = v;
	nod2[tot].c = c;
}

void spfa() {
	priority_queue<pair<int, int> > heap;
	for (int i = 1; i <= n; ++i) {
		d[i] = inf;
		finish[i] = false;
	}
	d[1] = 0;
	heap.push(make_pair(-d[1], 1));
	while (!heap.empty()) {
		int x = heap.top().second;
		heap.pop();
		if (finish[x]) {
			continue;
		}
		finish[x] = true;
		for (int p = head[x]; p > -1 ; p = nod[p].nxt)
			if (d[nod[p].to] > d[x] + nod[p].w)
			{	
				d[nod[p].to] = d[x] + nod[p].w;
				heap.push(make_pair(-d[nod[p].to], nod[p].to));
			}
	}
}
void init() {
	tot = -1;
	for (int i = 1; i <= n; i++) head[i] = -1;
	for (int i = 1; i <= m; i++) {
		int u, v, ww;
		scanf("%d%d%d", &u, &v, &ww);
		add1(u, v, ww);
		add1(v, u, ww);
		e[i].u = u;
		e[i].v = v;
		e[i].w = ww;
	}
}

void build_graph() {
	S = 1;
	T = n;
	for (int i = 1;i <= n; i++) head2[i] = -1;
	tot = -1;
	
	for (int i = 1; i <= m ; i++) {
		int u = e[i].u, v = e[i].v;
		if (d[u] == d[v] + e[i].w) {
			add2(v, u, 1);
			add2(u, v, 0);
			continue;
		}
		if (d[v] == d[u] + e[i].w) {
			add2(u, v, 1);
			add2(v, u, 0);
			continue;
		}
	}
}
void getans2() {
	int l = 0, r = 1;
	q[1] = 1;
	for (int i = 1; i <= n ; i++) d[i] = -1;
	d[1] = 0;
	while (l < r) {
		int t = q[++l];
		for (int p = head2[t]; p > -1; p = nod2[p].nxt) {
			if (d[nod2[p].to] == -1) {
				d[nod2[p].to] = d[t] + 1;
				q[++r] = nod2[p].to;
			}
		}
	}
	ans2 = m - d[n];
}
int bfs() {
	int l = 0 ,r = 1;
	q[1] = S;
	for (int i = 0; i <= T ; i++) d[i] = -1;
	d[S] = 0;
	while (l < r) {
		int t = q[++l];
		for (int p = head2[t]; p > -1; p = nod2[p].nxt) {
			if (d[nod2[p].to] == -1 && nod2[p].c) {
				d[nod2[p].to] = d[t] + 1;
				q[++r] = nod2[p].to;
			}
		}
	}
	return d[T]>-1;
}
int dfs(int u, int ext) {
	if (u == T) return ext;
	 int p = w[u], ret = 0;
	 for (; p > -1; p = nod2[p].nxt, w[u] = p) {
	 	if (ext <= 0) break;
	 	if (nod2[p].c && d[nod2[p].to] == d[u] +1) {
	 		int flow = dfs(nod2[p].to, min(ext, nod2[p].c));
	 		ext -= flow; ret += flow;
	 		nod2[p].c -= flow; nod2[p^1].c += flow;
		}
	}
	if (p == -1) d[u] = -1;
	return ret;
}
void dinic() {
	ans1 = 0;
	while (bfs()) {
		for (int i = S ;i <= T; i++) w[i] = head2[i];
		ans1 += dfs(S,inf);
	}
}
void solve() {
	spfa();
	build_graph();
	getans2();
	dinic();
	printf("%d %d\n", ans1, ans2);
}

int main()	{
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		solve();
	}
	return 0;
}
