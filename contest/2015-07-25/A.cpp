#include <cstdio>
#include <iostream>

using namespace std;

const long long MOD = 1e9 + 7;

const int N = 222222;

int n;
int a[N], pos[N], l[N], r[N];

void solve(void) {
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= 10000; ++i) {
		pos[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		l[i] = pos[a[i]];
		for (int j = a[i]; j <= 10000; j += a[i]) {
			pos[j] = i;
		}
	}
	for (int i = 1; i <= 10000; ++i) {
		pos[i] = n + 1;
	}
	for (int i = n; i >= 1; --i) {
		r[i] = pos[a[i]];
		for (int j = a[i]; j <= 10000; j += a[i]) {
			pos[j] = i;
		}
	}
	
	long long ans = 0;
	for (int i = 1; i <= n; ++i) {
		ans += 1LL * (i - l[i]) * (r[i] - i);
		ans %= MOD;
	}
	cout << ans << endl;
}

int main(void) {
	for (; ~scanf("%d", &n); solve());
}
