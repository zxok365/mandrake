#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N = 111111;
int a[N], n, m;
int sum[N], maxn[N], minn[N];
void solve() {
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	sum[0] = 0;
	for (int i = 1; i <= n; i++) {
		sum[i] = (sum[i - 1] + a[i] % m + m) % m;
	}
	for (int i = 0; i < m; i++) {
		minn[i] = n + 1;
		maxn[i] = 0;
	} 
	for (int i = 0; i <= n; i++) {
		minn[sum[i]] = min(minn[sum[i]], i);
		maxn[sum[i]] = max(maxn[sum[i]], i);
	}
	int ans = 0;
	for (int i = 0; i < m; i++) {
		ans = max(ans, maxn[i] - minn[i]);
	}
	printf("%d\n", ans);
}
int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		solve();
	}
}
