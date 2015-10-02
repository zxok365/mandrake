#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N = 111111;
int n, m;
long long w[N];
void solve() {
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &w[i]);
		w[i] *= 2;
	}
	
	for (int i = 1; i <= m; i++) {
		int u, v;
		long long ww;
		scanf("%d%d%lld", &u, &v, &ww);
		w[u] += ww;
		w[v] += ww;
	}

	sort(w + 1, w + n + 1);
	reverse(w + 1, w + n + 1);
	
	long long ans = 0;
	for (int i = 1; i <= n; i++) {
		if (i & 1) ans += w[i];
		else ans -= w[i];
	}
	
	ans /= 2;
	printf("%lld\n", ans);
}

int main() {
	while (scanf("%d%d", &n, &m) == 2) {
		solve();
	}
	return 0;
}
