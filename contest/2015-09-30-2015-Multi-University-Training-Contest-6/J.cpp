#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>

using namespace std;

const int N = 2017;
const int mod = (int)1e9 + 7;

int f[N][N];
int base[N];
int n, m;

__inline void update(int &x, int y) {
	x += y;
	if (x >= mod) {
		x -= mod;
	}
}

__inline void solve() {
	scanf("%d%d", &n, &m);
	
	base[0] = 1;
	for (int i = 1; i <= n; i++) {
		base[i] = 1LL * base[i - 1] * m % mod;
	}
	
	f[1][1] = m;
	f[1][0] = 0;
	for (int i = 2; i <= n; i++) {
		int k = min(i, m);
		for (int j = (i & 1) ? 1 : 0; j <= k; j += 2) {
			f[i][j] = 0;
			if (j > 0) update(f[i][j], 1LL * f[i - 1][j - 1] * (m - j + 1) % mod);
			if (j < m) update(f[i][j], 1LL * f[i - 1][j + 1] * (j + 1) % mod);
		}
	}
	
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		update(ans, 1LL * (1LL * f[i][i & 1] * (n - i + 1) % mod) * base[n - i] % mod);
	}
	
	printf("%d\n", ans);
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
}

