#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

const int MAXS = (1 << 12) + 11;
const int M = 555;
const int N = 22;
using namespace std;
long long f[MAXS][M];
int score[N][N];
long long gcd(long long x, long long y){
	if (y == 0) return x;
	else return gcd(y, x % y);	
}

void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &score[i][j]);
	
	memset(f, 0, sizeof f);
	f[0][0] = 1;
	for (int state = 0; state < (1 << n); state++) {
		for (int now = 0; now <= m; now++) {
			if (f[state][now] == 0) continue;
			int cnt = 0;
			for (int i = 1; i <= n; i++) {
				if (state >> i - 1 & 1) ++cnt;
			}
			for (int i = 1; i <= n; i++) {
				if (~state >> i - 1 & 1) {
					int tag = now + score[i][cnt + 1];
					f[state ^ (1 << i - 1)][tag >= m ? m : tag] += f[state][now];
				}
			}
		}	
	}
	
	long long up = 1;
	for (int i = 1; i <= n; i++)
		up *= i;
	
	long long down = f[(1 << n)- 1][m];
	if (down == 0) {
		puts("No solution");
		return;
	}
	
	long long tmp = gcd(up, down);
	up /= tmp; down /= tmp;
	
	cout << up << "/" << down << endl;
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (;tests--;solve());
	return 0;
}
