#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 222;
int a[N], fa[N], h[N];
int getfa(int x) {
	return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}

void set_union(int x, int y) {
	int fx = getfa(x);
	int fy = getfa(y);
	fa[fx] = fy;
}

void solve() {
	int n, k;
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= n; i++) fa[i] = i;
	sort(a + 1, a + n + 1);
	for (int i = 1; i < n; i++) {
		if (a[i + 1] - a[i] <= k) set_union(i, i + 1);
	}
	for (int i = 1; i <= n; i++) h[i] = 0;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!h[getfa(i)]) ans++;
		h[getfa(i)] = 1;
	}
	printf("%d\n", ans);
}	
int main() {
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++) {
		printf("Case #%d: ",tt);
		solve();
	}
}
