#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1111;

int n, k;
int visit[N];

void solve() {
	std::vector<int> prime, big;
	
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= k; i++) {
		int x;
		scanf("%d", &x);
		if (x * x <= n) {
			prime.push_back(x);
		} else {
			big.push_back(x);
		}
	}
	
	int answer = 0;
	
	int tot = prime.size();
	for (int mask = 0; mask < (1 << tot); mask++) {
		for (int i = 1; i <= n; ++i) {
			visit[i] = 0;
		}
		for (int i = 0; i < tot; ++i) {
			if (mask >> i & 1) {
				for (int j = prime[i]; j <= n; j += prime[i]) {
					visit[j] ^= 1;
				}
			}
		}
		for (int i = 0; i < (int)big.size(); ++i) {
			int total[2] = {0, 0};
			for (int j = big[i]; j <= n; j += big[i]) {
				total[visit[j]]++;
			}
			if (total[0] > total[1]) {
				for (int j = big[i]; j <= n; j += big[i]) {
					visit[j] ^= 1;
				}
			}
		}
		int total = 0;
		for (int i = 1; i <= n; ++i) {
			total += visit[i];
		}
		answer = std::max(answer, total);
 	}
 	printf("%d\n", answer);
}
int main() {
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++) {
		printf("Case #%d: ", tt);
		solve();
	}
	return 0;
}
