#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

void solve() {
	int x1, x2, x3, y1, y2, y3;
	scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
	int ans = x1 * y2 - x2 * y1;
	ans = gcd(ans, x2 * y3 - x3 * y2);
	ans = gcd(ans, x1 * y3 - x3 * y1);
	printf("%d\n", abs(ans));
}

int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		printf("Case #%d: ", i);
		solve();
	}
	return 0;
}

