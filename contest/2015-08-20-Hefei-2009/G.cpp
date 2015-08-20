#include <cstdio>
#include <cstring>
#include <vector>

const int MOD = 1e9 + 7;

const int N = 111;

int n, m, s, stamp;
std::vector<int> edge[N];
int value[N], ways[N][N][N];
int comb[11111][111];

int dfs(int x) {
	if (value[x] == -1) {
		bool visit[N];
		memset(visit, 0, sizeof(visit));
		
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			visit[dfs(y)] = true;
		}
		for (int i = 0; ; ++i) {
			if (!visit[i]) {
				value[x] = i;
				break;
			}
		}
	}
	return value[x];
}

void solve(void) {
	scanf("%d%d%d", &n, &m, &s);
	for (int i = 0; i < n; ++i) {
		value[i] = -1;
		edge[i].clear();
	}
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x].push_back(y);
	}
	for (int i = 0; i < n; ++i) {
		dfs(i);
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			for (int k = 0; k <= n; ++k) {
				ways[i][j][k] = 0;
			}
		}
	}
	for (int i = 0; i <= n; ++i) {
		ways[i][0][0] = 1;
	}
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 0; k <= n; ++k) {
				ways[i][j][k] = (ways[i - 1][j][k] + ways[i - 1][j - 1][k ^ value[i - 1]]) % MOD;
			}
		}
	}
	int answer = 0;
	for (int i = 0; i <= n && i <= s; ++i) {
		int rest = s - i;
		if (rest % 2 == 0) {
			answer = (answer + 1LL * ways[n][i][0] * comb[rest / 2 + n - 1][n - 1] % MOD) % MOD;
		}
	}
	printf("%d\n", answer);
}

void prepare() {
	for (int i = 0; i <= 10000; ++i) {
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < std::min(i, 100); ++j) {
			comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
		}
	}
}

int main(void) {
	prepare();
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
