#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

const long long MOD = 258280327;

const int N = 100001;

int n;
long long fact[N], mu[N], sum1[N], sum2[N], counter[N], inverse[N];
std::vector<int> factor[N];

__inline long long _inverse(const long long &x) {
	if (x == 1) {
		return 1;
	} else {
		return (MOD - MOD / x) * _inverse(MOD % x) % MOD;
	}
}

void prepare(void) {
	fact[0] = 1;
	for (int i = 1; i < N; ++i) {
		fact[i] = fact[i - 1] * i % MOD;
	}
	for (int i = 0; i < N; ++i) {
		inverse[i] = _inverse(fact[i]);
	}
	for (int i = 1; i < N; ++i) {
		for (int j = i; j < N; j += i) {
			factor[j].push_back(i);
		}
	}
	for (int i = 1; i < N; ++i) {
		mu[i] = (i == 1 ? 1 : 0) - mu[i];
		for (int j = i + i; j < N; j += i) {
			mu[j] += mu[i];
		}
	}
}

__inline long long comb(const long long &n, const long long &k) {
	return (fact[n] * inverse[k] % MOD) * inverse[n - k] % MOD;
}

void solve(void) {
	int limit = 0;
	for (int i = 0; i < n; ++i) {
		int number;
		scanf("%d", &number);
		for (int j = 0; j < (int)factor[number].size(); ++j) {
			counter[factor[number][j]]++;
		}
		limit = std::max(limit, number);
	}
	
	for (int i = 1; i <= limit; ++i) {
		sum1[i] = sum2[i] = 0;
		for (int j = 1; j <= counter[i]; ++j) {
			(sum1[i] += (comb(counter[i], j) * fact[j] % MOD) * fact[n - j + 1] % MOD) %= MOD;
		}
		for (int j = 0; j <= counter[i]; ++j) {
			(sum2[i] += comb(counter[i], j) * j % MOD) %= MOD;
		}	
	}
	
	long long result1 = 0, result2 = 0;
	for (int i = 1; i <= limit; ++i) {
		long long answer1 = 0, answer2 = 0;
		for (int j = i; j <= limit; j += i) {
			(answer1 += mu[j / i] * sum1[j] % MOD) %= MOD;
			(answer2 += mu[j / i] * sum2[j] % MOD) %= MOD;
		}
		(result1 += answer1 * i % MOD) %= MOD;
		(result2 += answer2 * i % MOD) %= MOD;
	}
	
	if (result1 > result2) {
		printf("Mr. Zstu %d\n", (int)result1);
	} else if (result1 < result2) {
		printf("Mr. Hdu %d\n", (int)result2);
	} else {
		printf("Equal %d\n", (int)result1);
	}
	for (int i = 1; i <= limit; ++i) {
		counter[i] = 0;
	}
}

int main(void) {
	prepare();
	for (; ~scanf("%d", &n); solve());
}
