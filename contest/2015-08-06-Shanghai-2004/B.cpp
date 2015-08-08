#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define GG pair<int, pair<int, int> >
using namespace std;
const int N = 100;
const int inf = 12343210;
char mat[N][N];
const int dx[5] = {-1, 0, 1, 0, 0};
const int dy[5] = {0, 1, 0, -1, 0};

int movement[N][N], sumx[N][N], sumy[N][N], moved[N][N];
int n, m;
int getpos(int x, int y) {
	return (x - 1) * m + y;
}
int getx(int t) {
	return t % m ? t / m  + 1 : t / m;
}
int gety(int t) {
	return t % m ? t % m : m;
}
void out() {
	for (int i = 1; i <= n; i++) {
 		for (int j = 1; j <= m; j++) {
 			putchar(mat[i][j] == '*' ? '.' : mat[i][j]);
		}
		puts("");
	}
	puts("----------------");
}
bool move() {
	bool flg = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			moved[i][j] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (mat[i][j] == '*') continue;
			int tp = movement[i][j];
			int tx = i + dx[tp], ty = j + dy[tp];
			if (moved[i][j] || mat[tx][ty] != '*' || tx < 1 || tx > n || ty < 1 || ty > m) continue;
			mat[tx][ty] = mat[i][j];
			movement[tx][ty] = movement[i][j];
			moved[tx][ty] = 1;
			mat[i][j] = '*';
			flg = 1;
		}
	return flg;
}
void chongsuan() {
	for (int i = 1 ; i <= n; i++) {
		sumx[i][0] = 0;
		for (int j = 1; j <= m; j++)
			sumx[i][j] = sumx[i][j - 1] + (mat[i][j] != '*');
		sumx[i][m + 1] = sumx[i][m];
	}
	for (int i = 1; i <= m; i++) {
		sumy[i][0] = 0;
		for (int j = 1; j <= n; j++)
			sumy[i][j] = sumy[i][j - 1] + (mat[j][i] != '*');
		sumy[i][n + 1] = sumy[i][n];
	}
}
void Clear(int p1, int p2) {
	int x1 = getx(p1) , y1 = gety(p1), x2 = getx(p2), y2 = gety(p2) ;
	mat[x1][y1] = mat[x2][y2] = '*'; 	
	for (;move() ;);
	chongsuan();
}

bool check1(int x1, int y1, int x2, int y2) {
	if (x1 != x2 && y1 != y2) return 0;
	if (x1 == x2) {
		if (y1 > y2) swap(y1, y2);
		return (sumx[x1][y2] == sumx[x1][y1] + 1);
	}
	if (x1 > x2) swap(x1, x2);
	return (sumy[y1][x2] == sumy[y1][x1] + 1);
}

bool check2(int x1, int y1, int x2, int y2) {
	if (x1 == x2 || y1 == y2) return 0;
	bool flg = 0;
	int tx = x1, ty = y2;
	if (mat[tx][ty] == '*') {
		flg |= (sumx[x1][max(ty, y1) - 1] == sumx[x1][min(ty, y1)]) && (sumy[y2][max(x1 ,x2) - 1] == sumy[y2][min(x1, x2)]);
	}
	tx = x2, ty = y1;
	if (mat[tx][ty] == '*') {
		flg |= (sumx[x2][max(ty, y2) - 1] == sumx[x2][min(ty, y2)]) && (sumy[y1][max(x1, x2) - 1] == sumy[y1][min(x1, x2)]);
	}
	return flg;
}

bool check3(int x1, int y1, int x2, int y2) {
	if (x1 > x2) {
		swap(x1, x2);
		swap(y1, y2);
	}
	
	for (int i = x1 + 1; i <= n + 1; i++) {
		if (mat[i][y1] != '*' || mat[i][y2] != '*') continue;
		if (sumy[y1][x1] != sumy[y1][i]) break;
		if (i == x2) continue;
		if (i < x2) if (sumy[y2][x2] - sumy[y2][i] > 1) continue;
		if (i > x2)	if (sumy[y2][i] != sumy[y2][x2]) break;
		if (sumx[i][min(y1, y2) - 1] != sumx[i][max(y1, y2)]) continue;
		return 1; 
	}
	for (int i = x1 - 1; i >= 0; i--) {
		if (mat[i][y1] != '*' || mat[i][y2] != '*') continue;
		if (sumy[y1][x1] - sumy[y1][i] > 1) break;
		if (sumy[y2][x2] - sumy[y2][i] > 1) break;
		if (sumx[i][min(y1, y2) - 1] != sumx[i][max(y1, y2)]) continue;
		return 1; 
	}
	if (y1 > y2) {
		swap(y1, y2);
		swap(x1, x2);
	}
	
	
	for (int i = y1 + 1; i <= m + 1; i++) {
		if (mat[x1][i] != '*' || mat[x2][i] != '*') continue;
		if (sumx[x1][i] != sumx[x1][y1]) break;
		if (i == y2) continue;
		if (i < y2) if (sumx[x2][y2] - sumx[x2][i] > 1) continue;
		if (i > y2) if (sumx[x2][i] != sumx[x2][y2]) break;
		if (sumy[i][min(x1, x2)] != sumy[i][max(x1, x2) - 1]) continue;
		return 1; 
	}
	for (int i = y1 - 1; i >= 0; i--) {
		if (mat[x1][i] != '*' || mat[x2][i] != '*') continue;
		if (sumx[x1][y1] - sumx[x1][i] > 1) break;
		if (sumx[x2][y2] - sumx[x2][i] > 1) break;
		if (sumy[i][min(x1, x2) - 1] != sumy[i][max(x1, x2)]) continue;
		return 1;
	}
	return 0;
}
void chkmin(GG &p1, GG p2) {
	p1 = min(p1, p2);
}

bool lianliankan() {
	GG nowans = make_pair(123, make_pair(inf, inf));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (mat[i][j] != '*') {
				for (int p = i; p <= n; p++)
					for (int q = 1; q <= m; q++) {
						if (p == i && q <= j) continue;
						if (mat[p][q] == '*' || mat[p][q] != mat[i][j]) continue;
						if (check1(i, j, p, q)) {
							Clear(getpos(i, j), getpos(p, q));
							return 1;
						}
						if (check2(i, j, p, q))  {
							chkmin(nowans, make_pair(2, make_pair(getpos(i,j), getpos(p, q))));
							continue;
						}
						if (check3(i, j, p, q)) {
							chkmin(nowans, make_pair(3, make_pair(getpos(i,j), getpos(p, q))));
							continue;	
						}
					}
			} 
		}
	if (nowans.first != 123) {
		Clear(nowans.second.first, nowans.second.second);
		return 1;
	}
	return 0;
}

void solve() {
	char s[100];
	for (int i = 0; i <= n + 1; i++)
	 	for (int j = 0; j <= m + 1; j++)
	 	 	mat[i][j] = '*';
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++){
 			scanf("%s", s);
 			mat[i][j] = s[0];
 			if (s[1] == 'U')
 			movement[i][j] = 0;
 			else
 			if (s[1] == 'R') 
 			movement[i][j] = 1;
 			else
 			if (s[1] == 'D')
 			movement[i][j] = 2;
 			else
 			if (s[1] == 'L') 
 			movement[i][j] = 3;
 			else
 			if (s[1] == 'S') 
 			movement[i][j] = 4;
 		}
 	memset(sumx, 0, sizeof sumx);
 	memset(sumy, 0, sizeof sumy);
 	chongsuan();
 	for (;lianliankan(););
 	for (int i = 1; i <= n; i++) {
 		for (int j = 1; j <= m; j++) {
 			putchar(mat[i][j] == '*' ? '.' : mat[i][j]);
		}
		puts("");
	}
}

int main() {
	for (; scanf("%d%d", &n, &m) && (n > 0 || m > 0); solve()) {
		static int tests = 0;
		printf("Case %d\n", ++tests);
	}	
	return 0;
}
