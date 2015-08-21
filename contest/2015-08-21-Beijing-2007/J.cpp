#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>

using namespace std;

int n;
long double a, b;

long double get(const long double &f, const long double &p) {
	long double prob = 1 / (1 + pow(p - a, b));
	return f + (p - f) * prob;
}

long double read() {
	double x;
	scanf("%lf", &x);
	return x;
}

void work() {
	a = read(), b = read();

	long double f = a;
	for(int i = 2; i <= n; i++) {
		long long left = a, right = 1e10;
		while (right - left > 10) {
			long long mid1 = (left * 2 + right) / 3;
			long long mid2 = (left + right * 2) / 3;
			if (get(f, mid1) < get(f, mid2)) {
				left = mid1;
			} else {
				right = mid2;
			}
		}

		long double prev = f;
		f = 0;
		for (long long j = left; j <= right; ++j) {
			f = max(f, get(prev, j));
		}
	}
	printf("%.2f\n", (double)f);
}

int main()
{
	scanf("%d", &n);
	int test = 0;
	while(n)
	{
		printf("Case %d: ", ++test);
		work();
		scanf("%d", &n);
	}
	return 0;
}
