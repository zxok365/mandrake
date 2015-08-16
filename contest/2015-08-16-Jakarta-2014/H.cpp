#include <cstdio>

const int N = 2222;

int n, m, k;
char text[N];
char winner[N][N];

char dfs(int turn, int rest) {
	char &result = winner[turn][rest];
	if (result != 'C') {
		return result;
	}
	if (rest <= k) {
		return result = text[turn];
	}
	for (int eat = k; eat >= 1; --eat) {
		if (dfs(turn + 1, rest - eat) == text[turn]) {
			return result = text[turn];
		}
	}
	if (text[turn] == 'A') {
		return result = 'B';
	} else {
		return result = 'A';
	}
}

void solve() {
	scanf("%d%d%d%s", &n, &m, &k, text + 1);
	for (int i = 0; i <= n * 2; ++i) {
		for (int j = 0; j <= m; ++j) {
			winner[i][j] = 'C';
		}
	}
	printf("%c\n", dfs(1, m));
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}
