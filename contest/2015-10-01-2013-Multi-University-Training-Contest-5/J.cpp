#include <cstdio>

int q, m, n;

void solve(void) {
	for (int i = 0; i < q; ++i) {
		int type;
		scanf("%d%d%d", &type, &m, &n);
		double answer = 0;
		if (type == 0) {
			double number = 1;
			for (int j = 1; j <= n; ++j) {
				answer += number;
				number *= m;
			}
		} else {
			double number = 1;
			for (int j = 1; j <= n; ++j) {
				answer += number;
				number *= 1. * m / (m - j);
			}
		}
		printf("%.6f\n", answer);
	}
}

int main(void) {
	for (; ~scanf("%d", &q); solve());
}
