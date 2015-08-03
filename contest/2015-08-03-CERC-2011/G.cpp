#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 111;

const int dirx[] = {0, 0, 1, -1};
const int diry[] = {1, -1, 0, 0};

int n, m, stamp;
char a[N][N];
vector<int> edge[N * N];
int match[N * N], visit[N * N];

__inline int pos(int x, int y) {
	return x * m + y;
}

bool dfs(int x) {
	for (int i = 0; i < (int)edge[x].size(); ++i) {
		int y = edge[x][i];
		if (visit[y] != stamp) {
			visit[y] = stamp;
			if (match[y] == -1 || dfs(match[y])) {
				match[y] = x;
				match[x] = y;
				return true;
			}
		}
	}
	return false;
}

void solve(void) {
	for (int i = 0; i < n * m; ++i) {
		edge[i].clear();
	}
	for (int i = 0; i < n; ++i) {
		scanf("%s", a[i]);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == '.') {
				for (int k = 0; k < 4; ++k) {
					int x = i + dirx[k];
					int y = j + diry[k];
					if (x >= 0 && x < n && y >= 0 && y < m && a[x][y] == '.') {
						edge[pos(i, j)].push_back(pos(x, y));
					}
				}
			}
		}
	}
	
	for (int i = 0; i < n * m; ++i) {
		match[i] = -1;
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (((i + j) & 1) && a[i][j] == '.') {
				stamp++;
				dfs(pos(i, j));
			}
		}
	 }
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j] == 'X') {
				putchar('X');
			} else {
				if (match[pos(i, j)] == -1) {
					putchar('B');
				} else {
					stamp++;
					if (dfs(match[pos(i, j)])) {
						match[pos(i, j)] = -1;
						putchar('B');
					} else {
						putchar('A');
					}
				}
			}
		}
		puts("");
	}
	puts("");
}

int main() {
	for (; ~scanf("%d%d", &n, &m) && (n || m); solve());
}
