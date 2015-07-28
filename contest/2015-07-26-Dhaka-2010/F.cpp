#include <cstdio>

using namespace std;

const int N = 111;

int n, k;
int a[N][N], b[N][N];

void solve(void) {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", a[i] + j);
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			scanf("%d", b[i] + j);
		}
	}
	
	int counter = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			counter += (a[i][j] != b[i][j]);
		}
	}
	
	if (counter == 0) {
		puts("0");
		return;
	}
	
	bool symmetric = true;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (b[i][j] != b[j][i]) {
				symmetric = false;
			}
		}
	}
	
	if (symmetric) {
		puts("-1");
		return;
	}
	
	int counter1 = 0, counter2 = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {
			counter1 += (a[i][j] != b[j][i] || a[j][i] != b[i][j]);
			counter2 += (a[i][j] != b[i][j] || a[j][i] != b[j][i]) && b[i][j] != b[j][i];
		}
	}
	
	//	enough
	if (counter1 > 0 || counter2 > 1) {
		printf("%d\n", counter);
		return;
	}
	
	//	no solution
	if (n <= 2 && k <= 2) {
		puts("-1");
		return;
	}
	
	if (k <= 2) {
		printf("%d\n", counter + 2);
		return;
	}
	
	printf("%d\n", counter + 1);
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case %d: ", i);
		solve();
	}
}
