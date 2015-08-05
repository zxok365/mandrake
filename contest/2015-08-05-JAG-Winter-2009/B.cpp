#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int MAXN = 2000;
vector<int> adj[MAXN];
int n, m, visit[MAXN], matchy[MAXN], times;
bool dfs(int x) {
	for (int i = 0; i < (int)adj[x].size(); i++) {
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
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int k;
		scanf("%d", &k);
		for (int j = 1; j <= k; j++) {
			int to;
			scanf("%d", &to);
			adj[i].push_back(to);
		}
	}
	memset(matchy, 0, sizeof matchy);
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		times++;
		ans += dfs(i);
	}
	if (ans < m) puts("Alice");
	else puts("Bob");
	return 0;
}
