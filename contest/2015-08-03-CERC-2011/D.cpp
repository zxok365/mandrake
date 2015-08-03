#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
const int MAXN = 1011;
char s2[MAXN][MAXN];
char s[MAXN][MAXN];
char code[MAXN][MAXN];
char ans[MAXN][MAXN];
void move() {
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++)
			s2[j][n + 1 - i] = s[i][j];
	
	for (int i = 1 ; i <= n; i++)
		for (int j = 1; j <= n; j++)
			s[i][j] = s2[i][j];
}

int main() {
	
	while (scanf("%d", &n) == 1 && n != 0) {
		for (int i = 1; i <= n; i++)
			scanf("%s", s[i] + 1);
		for (int i = 1; i <= n; i++)
			scanf("%s", code[i] + 1);
		
		for (int rot = 1; rot <= 4; rot++) {
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (s[i][j] == 'O') {
						putchar(code[i][j]);
					}
			move();
		}
		puts("");
	}

	return 0;
}
