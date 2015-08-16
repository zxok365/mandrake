#include <cstdio>
#include <vector>

const int MOD = 1e9 + 7;

int n, m, k, stamp;
int comb[200][200];
int ways[10][1000][100];
int visit[10][1000][100];
std::vector<int> value[10][10];

void update(int &x, int y) {
	x += y;
	x %= MOD;
	x += MOD;
	x %= MOD;
}

int dfs(int row, int can, int remain) {
	int &result = ways[row][can][remain];
	if (visit[row][can][remain] == stamp) {
		return result;
	}
	visit[row][can][remain] = stamp;
	if (row == n) {
		return result = (can >> m - 1 & 1) && remain == 0;
	}
	result = 0;
	for (int used = 0; used <= remain && used <= m; ++used) {
		for (int index = 0; index < (int)value[m][used].size(); ++index) {
			int ban = value[m][used][index];
			
			int mask = 0;
			for (int i = 0; i < m; ++i) {
				if (ban >> i & 1) {
					continue;
				}
				if ((can >> i & 1) || (i > 0 && (mask >> i - 1 & 1))) {
					mask ^= 1 << i;
				} 
			}
			update(result, dfs(row + 1, mask, remain - used));
		}
	}
	return result;
}

void solve(void) {
	stamp++;
	
	scanf("%d%d%d", &n, &m, &k);
	int answer = 0;
	for (int i = 0; i <= k; ++i) {
		update(answer, comb[n * m][i]);
	}
	for (int i = 0; i <= k; ++i) {
		update(answer, -dfs(0, 1, i));
	}
	printf("%d\n", answer);
}

int main(void) {
	comb[0][0] = 1;
	for (int i = 1; i <= 100; ++i) {
		comb[i][0] = comb[i][i] = 1;
		for (int j = 1; j < i; ++j) {
			comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % MOD;
		}
	}
	for (int n = 1; n <= 8; ++n) {
		for (int mask = 0; mask < (1 << n); ++mask) {
			value[n][__builtin_popcount(mask)].push_back(mask);
		}
	}
	
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case #%d: ", i);
		solve();
	}
}
