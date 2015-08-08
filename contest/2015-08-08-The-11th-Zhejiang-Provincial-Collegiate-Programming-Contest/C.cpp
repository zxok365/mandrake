#include <cstdio>
#include <algorithm>

int n, m;

void solve(void) {
	scanf("%d%d", &n, &m);
	int total = 0, maximum = 0;
	for (int i = 0; i < n; ++i) {
		int number;
		scanf("%d", &number);
		total += number;
		maximum = std::max(maximum, number);
	}
	maximum = std::max(maximum, total / m + (total % m != 0));
	printf("%d\n", maximum);
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
