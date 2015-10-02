#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
const int N = 50 * 50 + 111;
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0}; 

int g[52][52][52][52];
int bx, by, fx, fy;
int n, m, number;

pair<int, int> q[N];
int dist[55][55];
int go() {
	int l = 0, r = 1;
	q[1] = make_pair(bx, by);
	memset(dist, - 1, sizeof dist);
	dist[bx][by] = 0;
	while (l < r) {
		pair<int, int> now = q[++l];
		int nowx = now.first;
		int nowy = now.second;
		for (int dir = 0; dir < 4; dir++) {
			int tx = nowx + dx[dir];
			int ty = nowy + dy[dir];
			if (tx >= 0 && tx < n && ty >= 0 && ty < m) {
				if (g[nowx][nowy][tx][ty] > -1 && dist[tx][ty] == -1) {
					q[++r] = make_pair(tx, ty);
					dist[tx][ty] = dist[nowx][nowy] + 1;
					if (tx == fx && ty == fy) {
						return dist[tx][ty];
					}
				} 
			}
		}
	}
	return -1;
}
int main() {
	scanf("%d%d%d", &m, &n, &number);
	for (int t = 1; t <= number; t++) {
		int sx, sy, ex, ey;
		scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
		if (sx == ex && sx > 0) {
			for (int i = min(sy, ey); i < max(sy, ey); i++) {
				g[i][sx - 1][i][sx] = -1;
				g[i][sx][i][sx - 1] = -1;

			}
		}
		if (sy == ey && ey > 0) {
			for (int i  = min(sx, ex); i < max(sx, ex); i++) {
				g[sy - 1][i][sy][i] = -1;
				g[sy][i][sy - 1][i] = -1;
			}
		}
	}

	scanf("%d%d%d%d", &bx, &by, &fx, &fy);
	swap(bx, by);
	swap(fx, fy);
	int origin, ans;
	ans = go();
	origin = ans;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++) {
			if (g[i - 1][j - 1][i - 1][j] != -1) {
				g[i - 1][j - 1][i - 1][j] = -1;
				g[i - 1][j][i - 1][j - 1] = -1;
				ans = max(go(), ans);
				g[i - 1][j - 1][i - 1][j] = 0;
				g[i - 1][j][i - 1][j - 1] = 0;
			}
		}
	}
	for (int i = 1; i < n; i++) {
		for (int j = 1; j <= m; j++) {
			if (g[i - 1][j - 1][i][j - 1] != -1) {
				g[i - 1][j - 1][i][j - 1] = -1;
				g[i][j - 1][i - 1][j - 1] = -1;
				ans = max(go(), ans);
				g[i - 1][j - 1][i][j - 1] = 0;
				g[i][j - 1][i - 1][j - 1] = 0;
			}
		}
	}

	printf("%d\n", ans - origin);
	return 0;
}
