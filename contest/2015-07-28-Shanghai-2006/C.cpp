#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
const int MAXN = 200000;
using namespace std;

long long my_abs(const long long &x) {
	return (x < 0) ? -x : x;
}

struct Node {
	int to, nxt;
}nod[MAXN * 2];
long long inf = 1LL << 62;
long long sum[MAXN];
int w[MAXN];
int head[MAXN], vis[MAXN];
int n, m, tot;
void dfs(int x)	{
	sum[x] = w[x];
	for (int p = head[x]; p; p = nod[p].nxt) {
		if (!vis[nod[p].to]) {
			vis[nod[p].to] = 1;
			dfs(nod[p].to);
			sum[x] += sum[nod[p].to];
		}
	}
}

void clear() {
	for (int i = 1 ; i <= n; i++) head[i] = vis[i] = sum[i] = 0;
	tot = 0;
}

void add(int u, int v) {
	nod[++tot].nxt = head[u];
	head[u] = tot;
	nod[tot].to = v;
}

int main() {
	while (scanf("%d%d", &n, &m)&&(n > 0 || m > 0)) {
		static int tst = 0;
		clear();
		for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
		for (int i = 1; i < n; i++) {
			int u, v;
			scanf("%d%d", &u, &v);
			add(u,v);add(v,u);
		}
		vis[1] = 1;
		dfs(1);
		long long ans = inf;
		for (int i = 1; i <= n; i++)
			if (my_abs(sum[1] - sum[i] - sum[i]) < ans) ans = my_abs(sum[1] - sum[i] - sum[i]);
		printf("Case %d: ",++tst);
		cout<< ans <<endl;
	}
	return 0;
}
