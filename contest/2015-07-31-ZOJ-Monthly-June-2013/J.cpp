#include <cstdio>

using namespace std;

const long long MOD = 1e9 + 7;

const int N = 111111;

int n, m;
long long pow2[N], ways[N];

void solve(void) {
	pow2[0] = 1;
	for (int i = 1; i <= n; ++i) {
		pow2[i] = pow2[i - 1] * 2 % MOD;
	}
	
	for (int i = 0; i <= m; ++i) {
		ways[i] = 0;
	}
	
	ways[m] = 1;
	for (int i = m + 1; i <= n; ++i) {
		ways[i] = (ways[i - 1] * 2 + pow2[i - m - 1] - ways[i - m - 1]) % MOD;
	}
	
	ways[n] += MOD;
	ways[n] %= MOD;
	
	printf("%d\n", (int)ways[n]);
}

int main(void) {
	for (; ~scanf("%d%d", &n, &m); solve());
}
