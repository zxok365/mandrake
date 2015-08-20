#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>

using std::__gcd;

int a, b, c;

void solve(void) {
	printf("%d\n", a + b + c - __gcd(a, b) - __gcd(b, c) - __gcd(c, a) + __gcd(__gcd(a, b), c));
}

int main(void) {
	for (; scanf("%d%d%d", &a, &b, &c) && (a + b + c); solve());
}
