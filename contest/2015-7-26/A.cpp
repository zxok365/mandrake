#include <cstdio>

using namespace std;

int n;

void solve(void) {
	int ret = 0;
	for (int i = 0; i < n; ++i) {
		int x;
		scanf("%d", &x);
		ret += (x > 0) - (x == 0);
	}
	printf("%d\n", ret);
}

int main(void) {
	for (int tests = 1; ~scanf("%d", &n) && n; ++tests) {
		printf("Case %d: ", tests);
		solve();
	}
}
