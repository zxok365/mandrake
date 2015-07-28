#include <cstdio>
#include <iostream>

using namespace std;

int n;
long long fib[111];

void solve(void) {
	fib[0] = fib[1] = 1;
	for (int i = 2; i <= 50; ++i) {
		fib[i] = fib[i - 1] + fib[i - 2];
	}
	cin >> n;
	long long ans = 1;
	for (int i = 1; i <= n; ++i) {
		long long x;
		cin >> x;
		
		long long num = 0;
		for (int j = 50; j >= 0; --j) {
			if (x >= fib[j]) {
				x -= fib[j];
				num++;
			}
		}
		ans *= num;
	}
	cout << ans << endl;
}

int main(void) {
	ios::sync_with_stdio(false);
	int tests;
	cin >> tests;
	for (int i = 1; i <= tests; ++i) {
		cout << "Case " << i << ": ";
		solve();
	}
}
