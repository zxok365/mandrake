#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 111;
const int M = 111;
char s[N][M];
void solve() {
	int n, m;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);
	}
	m = strlen(s[1] + 1);
	
	int ans = 0;
	
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			if (s[i][j] == 'R' || s[i][j] == 'G') {
				ans++;
				int tx = i, ty = j;
				while (s[tx][ty] == 'R' || s[tx][ty] == 'G' && tx <= n && ty <= m) {
					if (s[tx][ty] == 'R') s[tx][ty] = '.';
					else s[tx][ty] = 'B';
					tx++; ty++;
				}
			}
		}
	
	for (int i = 1; i <= n; i++)
		for (int j = m; j >= 1; j--) {
			if (s[i][j] == 'B') {
				ans++;
				int tx = i, ty = j;
				while (s[tx][ty] == 'B' && tx <= n && ty >= 1) {
					s[tx][ty] = '.';
					tx++; ty--;
				}
			}
		}
	
	printf("%d\n", ans);
}
int main() {
	int test;
	scanf("%d", &test);
	for (int i = 1; i <= test; i++) {
		solve();
	}
	return 0;
}
