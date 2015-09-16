#include <cstdio>
#include <algorithm>
#include <climits>

const int N = 11111;

int n, m;
int a[N];

void solve(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	for (scanf("%d", &m); m--; ) {
		int left, right;
		scanf("%d%d", &left, &right);
		int answer = INT_MIN;
		for (int i = left; i <= right; ++i) {
			answer = std::max(answer, a[i]);
		}
		printf("%d\n", answer);
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
