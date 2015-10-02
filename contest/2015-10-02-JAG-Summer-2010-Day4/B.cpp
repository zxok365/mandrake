#include<cstdio>
#include<cmath>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<map>

using namespace std;

const int N = 15;

char str[N][N];

int dx[5] = {0, -1, 1, 0, 0};
int dy[5] = {0, 0, 0, 1, -1};

int k[N * N], need;
int bh[N][N], n, m, ban[277];
int dir[277];

typedef long long LL;

map<pair<pair<LL, int>, pair<int, int> > , bool> Q;

char type[5];

void out() {
	for(int i = 1; i <= need; i++) {
		printf("%c", type[k[i]]);
	}
	puts("");
	exit(0);
}

void dfs(int x, int y, int dir, int deep, long long mask) {
	if(Q.count(make_pair(make_pair(mask,dir), make_pair(x, y))))
		return ;
	Q[make_pair(make_pair(mask,dir), make_pair(x, y))] = true;
	if(mask == 0) {
		out();
		return ;
	}
	for(int i = 1; i <= 4; i++) {
		if(ban[dir] == i) continue;
		int nowx = x, nowy = y, tt = 0;
		while(1) {
			nowx += dx[i], nowy += dy[i];
			if(nowx <= 0 || nowx > n || nowy <= 0 || nowy > m)
				break;
			if(!bh[nowx][nowy]) continue;
			tt = bh[nowx][nowy]; break;
		}
		if(!tt) continue;
		bh[nowx][nowy] = 0;
		k[deep] = i;
		dfs(nowx, nowy, i, deep + 1, mask ^ (1LL << tt - 1));
		k[deep] = 0;
		bh[nowx][nowy] = tt;
	}
}

int main() {
	dir['U'] = 1; dir['D'] = 2;
	dir['R'] = 3; dir['L'] = 4;
	type[1] = 'U'; type[2] = 'D';
	type[3] = 'R'; type[4] = 'L';
	ban[1] = 2; ban[2] = 1;
	ban[3] = 4; ban[4] = 3;
	scanf("%d%d", &n, &m);
	need = 0;
	for(int i = 1; i <= n; i++)
		scanf("%s", str[i] + 1);
	pair<pair<int, int> , int > t;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++) {
			if(str[i][j] != '.' && str[i][j] != 'o') {
					t.first = make_pair(i, j); t.second = dir[str[i][j]];
			}
			if(str[i][j] == 'o')
				bh[i][j] = ++need;
		}
	dfs(t.first.first, t.first.second, t.second, 1, (1LL << need) - 1);
	return 0;
}
