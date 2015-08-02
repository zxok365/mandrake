#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
const int MAXN = 20000;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
struct Pos{
	int x, y, d, fnd;
}q[MAXN];
int f[30][30][4][2], n;
int g[30][30];
using namespace std;
void solve() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int d = 0; d < 4; d++)
				for (int fnd = 0; fnd < 2; fnd++)
					f[i][j][d][fnd] = -1;
	
	if (g[0][0] == 2) {
		puts("-1");
		return;
	}
	if (g[0][0] == 3) {
		puts("980");
		return;
	}
	
	int l = 0, r = 1;
	Pos position;
	position.x = 0;
	position.y = 0;
	position.d = 0;
	position.fnd = 0;
	q[r] = position;
	f[0][0][0][0] = 0;
	while (l < r) {
		Pos tmp = q[++l];
		for (int i = 0; i < 4; i++) {
			//move forward
			if (i == 0) {
				int nx = tmp.x + dx[tmp.d];
				int ny = tmp.y + dy[tmp.d];
				if (nx < n && ny < n && nx >= 0 && ny >= 0) {
					if (g[nx][ny] == 1 || g[nx][ny] == 2) continue;
					if (g[nx][ny] == 0 && f[nx][ny][tmp.d][tmp.fnd] == -1) {		
						Pos nxtposition;
						nxtposition.x = nx;
						nxtposition.y = ny;
						nxtposition.d = tmp.d;
						nxtposition.fnd = tmp.fnd;
						q[++r] = nxtposition;
						f[nx][ny][tmp.d][tmp.fnd] = f[tmp.x][tmp.y][tmp.d][tmp.fnd] + 1;
					}
					if (tmp.fnd == 0 && g[nx][ny] == 3 && f[nx][ny][tmp.d][1] == -1) {
						Pos nxtposition;
						nxtposition.x = nx;
						nxtposition.y = ny;
						nxtposition.d = tmp.d;
						nxtposition.fnd = 1;
						q[++r] = nxtposition;
						f[nx][ny][tmp.d][1] = f[tmp.x][tmp.y][tmp.d][tmp.fnd] + 2;
					}
				}
				continue;
			}
			
			int nx, ny, nd, nfnd;
			//turn left
			if (i == 1) {
				nx = tmp.x, ny = tmp.y, nd = tmp.d, nfnd = tmp.fnd;
				nd++;
				nd %= 4;
			}
			//turn right
			if (i == 2) {
				nx = tmp.x, ny = tmp.y, nd = tmp.d, nfnd = tmp.fnd;
				nd--;
				if (nd < 0) nd = 3;
			}
			if (f[nx][ny][nd][nfnd] == -1) {
				Pos nxtposition;
				nxtposition.x = nx;
				nxtposition.y = ny;
				nxtposition.d = nd;
				nxtposition.fnd = nfnd;
				q[++r] = nxtposition;
				f[nx][ny][nd][nfnd] = f[tmp.x][tmp.y][tmp.d][tmp.fnd] + 1;
			}
		}
	}	
	int	ans = -1;
	for (int d = 0; d < 4; d++) {
		//cout << f[0][0][d][1] << endl;
		if (f[0][0][d][1] > -1) { 
			ans = max(ans, (1000 - f[0][0][d][1] * 10 - 10));
		}
	}
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d",&T);
	for (; T--;) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) g[i][j] = 0;
		int tp, x, y;
		while (scanf("%d%d%d", &tp, &x, &y) && !(tp == -1 && x == -1 && y == -1)) {
			g[x][y] = tp;
		}
		solve();
		
	}
}
