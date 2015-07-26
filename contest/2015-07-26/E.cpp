#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 111;

int n, m;
int a[N];
int best[N][N];

int dfs(int left, int right) {
	if (left > right) {
		return 0;
	}
	if (~best[left][right]) {
		return best[left][right];
	}
	int &ret = best[left][right];
	ret = max(dfs(left + 1, right), dfs(left, right - 1));
	if (a[left] == a[right]) {
		ret = max(ret, dfs(left + 1, right - 1) + 1);
	}
	for (int k = left; k <= right; ++k) {
		ret = max(ret, dfs(left, k) + dfs(k, right));
	}
	return ret;
}

void solve(void) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			best[i][j] = -1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		best[i][i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	printf("%d\n", n - dfs(1, n));
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case %d: ", i);
		solve();
	}
}
