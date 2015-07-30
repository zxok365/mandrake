#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = (1 << 29);
const int MAXN = 100000;
const int HP = 1001;
const int ATK = 11;

struct Monster{
	int hp, atk, id;
}monster[MAXN];

int f[HP][HP][ATK];
int hp, atk, p, n;
pair<int, int> g[MAXN][10];

void update(pair<int, int> &p1, const pair<int, int> &p2) {
	if (p1.first < p2.first) p1 = p2;
	else if (p1.first == p2.first && p1.second > p2.second) p1 = p2;
}

int dfs(int a, int b ,int c) {
	if (b <= 0) {
		return 0;
	}
	
	if (a <= 0) {
		return INF;
	}
	if (~f[a][b][c]) {
		return f[a][b][c];
	}
	int &ret = f[a][b][c];

	ret = INF;
	ret = min(ret, dfs(a - c, b - atk, c));
	ret = min(ret, dfs(min(a + p, hp) - c, b - atk, c) + 1);
	if (a > c) {
		ret = min(ret, dfs(min(a - c + p, hp), b - atk, c) + 1);
	}
	return ret;
}

void solve() {
	for (int i = 1; i <=n; i++) {
		scanf("%d", &monster[i].id);
		if (monster[i].id == 1)
			scanf("%d%d", &monster[i].hp, &monster[i].atk);
	}
	scanf("%d%d%d",&hp, &atk, &p);
	
	memset(f, -1, sizeof(f));
	
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= 5; j++)
			g[i][j] = make_pair(-1, INF);
	
	g[0][0] = make_pair(0, 0);
	
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= 5; j++) {
			if (j == 0 && monster[i].id) {
				int bottle = dfs(hp, monster[i].hp, monster[i].atk);
				if (bottle < INF) {
					update(g[i][j], make_pair(g[i - 1][5].first + 1, g[i - 1][5].second + bottle));
				}
			} // beat boss
			
			if (monster[i].id) update(g[i][j], g[i - 1][j]); //skip boss
			else {
				if (j > 0) update(g[i][j], g[i - 1][j - 1]); // beat xiaobing
				if (j == 5) update(g[i][j], g[i - 1][j]); // beat xiaobing
			}
		}
		
	pair<int, int> ans;
	ans = make_pair(-1, INF);
	for (int state = 0; state <= 5; state++) {
 		update(ans, g[n][state]);
	}
	
	printf("%d %d\n", ans.first, ans.second);
}
int main() {
	while (scanf("%d", &n) != EOF) {
		solve();
	}
}
