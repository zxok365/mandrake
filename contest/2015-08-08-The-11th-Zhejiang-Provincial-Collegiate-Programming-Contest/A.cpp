#include <cstdio>

int n, m;

void solve(void) {
	scanf("%d%d", &n, &m);
	int answer1 = 0;
	for (int i = 0; i < n; ++i) {
		int number;
		scanf("%d", &number);
		answer1 += number;
	}
	int answer2 = 0;
	for (int i = 0; i < m; ++i) {
		int number;
		scanf("%d", &number);
		answer2 += number;
	}
	if (answer1 > answer2) {
		puts("Calem");
	} else if (answer1 < answer2) {
		puts("Serena");
	} else {
		puts("Draw");
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
