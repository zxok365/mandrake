#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <vector>

using namespace std;

const long long g[] = {0, 0, -1, -1, 0, -1, 1, -1, 0, 0, 1, -1, 0, -1, 1, 1, 0, -1, 0, -1, 0, 1, 1, -1, 0, 0, 1, 0, 0, -1, -1, -1, 0, 1, 1, 1, 0, -1, 1, 1, 0, -1, -1, -1, 0, 0, 1, -1, 0, 0, 0, 1, 0, -1, 0, 1, 0, 1, 1, -1, 0, -1, 1, 0, 0, 1, -1, -1, 0, 1, -1, -1, 0, -1, 1, 0, 0, 1, -1, -1, 0, 0, 1, -1, 0, 1, 1, 1, 0, -1, 0, 1, 0, 1, 1, 1, 0, -1, 0, 0, 0};
const int prime[]={2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};
vector <int> f;
void get_f(int r) {
	f.clear();
	for (int i = 0; prime[i] <= r; i++) {
		int tmp = f.size();
		for (int j = 0; j < tmp; j++) {
			if (prime[i] * f[j] <= 63) f.push_back(prime[i] * f[j]);
		}
		f.push_back(prime[i]);
	}
}

long long get_num(const long long &x ,int r) {
	get_f(r);
	long long ret = x - 1;
	for (int i = 0; i < f.size(); i++) {
		ret += ((long long)pow(x + 0.5, 1.0 / f[i]) - 1) * g[f[i]];
	}
	return ret;
}

void solve() {
	long long n; int r;
	cin >> n >> r;
	long long ans = n;
	for (; ; ) {
		long long temp = get_num(ans, r);
		if (temp == n) {
			break;
		}
		ans += (n - temp);
	}
	
	cout << ans << endl;
}

int main() {
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	for (int tt = 1; tt <= T; tt++) {
		solve();
	}
	return 0;
}
