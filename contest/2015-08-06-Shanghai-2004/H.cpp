#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1011;

int n, m;
int a[N], b[N];
int best[N][N];

__inline int calc(int x, int y) {
	if (x > y) {
		return 1;
	} else if (x == y) {
		return 0;
	} else {
		return -1;
	}
}

void solve(void) {
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", b + i);
	}
	
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	reverse(a + 1, a + n + 1);
	reverse(b + 1, b + n + 1);
	
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			best[i][j] = -(n + n);
		}
	}
	
	best[0][0] = 0;
	
	for (int i = 1; i <= n; ++i) {
		best[i][0] = best[i - 1][0] + calc(a[n + 1 - i], b[i]);
		best[i][i] = best[i - 1][i - 1] + calc(a[i], b[i]);
		
		for (int j = 1; j < i; ++j) {
			best[i][j] = max(best[i - 1][j - 1] + calc(a[j], b[i]), best[i - 1][j] + calc(a[n + 1 - i + j], b[i]));
		}
	}
	
	int result = -(n + n);
	for (int i = 0; i <= n; ++i) {
		result = max(result, best[n][i]);
	}
	printf("%d\n", result * 200);
}

int main(void) {
	for (; scanf("%d", &n) && n; solve());
}
