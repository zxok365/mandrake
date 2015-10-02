#include <cstdio>

const int mod = 1e9 + 7;

int n;

long long pow(const long long &x, const long long &k) {
	long long answer = 1, number = x;
	for (long long i = k; i > 0; i >>= 1) {
		if (i & 1) {
			(answer *= number) %= mod;
		}
		(number *= number) %= mod;
	}
	return answer;
}

void solve(void) {
	scanf("%d", &n);
	long long answer = (pow(2, n - 1) + mod - 1) % mod;
	printf("%d\n", (int)answer);
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
