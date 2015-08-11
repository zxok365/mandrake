#pragma comment(linker,"/STACK:102400000,102400000")

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int MAXN = 555555;
struct Edge {
	int to, nxt;
}nod[MAXN];

int n, tot;
int a[MAXN], f[MAXN], head[MAXN];
int getans(int x) {
	if (f[x] > -1) return f[x];
	else {
		int now = 0;
		for (int p = head[x]; p; p = nod[p].nxt) {
			now += getans(nod[p].to);
		}
		f[x] = now + 1;
		return f[x];
	}
}
void add(int x, int y) {
	nod[++tot].nxt = head[x];
	head[x] = tot;
	nod[tot].to = y;
}
void solve() {
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) head[i] = 0;
	tot = 0;
	for (int i = 1; i < n; i++) {	
		int u, v;
		scanf("%d%d", &u, &v);
		if (a[u] < a[v]) add(u, v);
		else add(v, u);
	}
	for (int i = 1; i <= n; i++) f[i] = -1;
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(getans(i), ans);
	printf("%d\n", ans);
}


int main() {
	while (scanf("%d", &n) == 1) {
		solve();
	}
	return 0;
}
