#include <iostream>
#include <cstdio>

using namespace std;
const int N = 1111;
const int inf = 1 << 29;
const int assist[4] = {0, 4, 8, 11};
int steepness[N];
int f[N][11][55][4];
void update(int &x, int y) {
	x = min(x, y);
}

void solve() {
	int n, m, energy;
	scanf("%d%d%d", &n, &m, &energy);
	for (int i = 1; i <= n; i++) scanf("%d", &steepness[i]);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= energy; k++)
				for (int pre = 0; pre <= 3; pre++)
					f[i][j][k][pre] = inf;
	
	
	f[0][m][energy][0] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= energy;k++) 
				for (int pre = 0; pre <= 3; pre++) {
					if (f[i][j][k][pre] >= inf) continue;
					
					if (j == 0 && pre > k) {
						update(f[i + 1][j][k][pre], f[i][j][k][pre] + steepness[i + 1]);
						continue;
					}
					
					for (int nxt = 0; nxt <= 3; nxt++) {
						if (nxt <= k) {
							if (nxt != pre) {
								if (j > 0) update(f[i + 1][j - 1][k - nxt][nxt], f[i][j][k][pre] +  max(steepness[i + 1] - assist[nxt], 0));
							}
							else
								update(f[i + 1][j][k - nxt][nxt], f[i][j][k][pre] +  max(steepness[i + 1] - assist[nxt], 0));
						}
					}
				}
	}
	
	int ans = inf;
	for (int k = 0; k <= m; k++)
		for (int rest = 0; rest <= energy; rest++)
			for (int pre = 0; pre <= 3; pre++)
				ans = min(ans, f[n][k][rest][pre]);
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++) {
		printf("Case #%d: ",tt);
		solve();
	}
	return 0;
}
