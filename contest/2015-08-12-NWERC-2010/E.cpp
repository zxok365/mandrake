#include <cstdio>
#include <vector>

const int N = 555;

int n, m;
std::vector<int> edge[N];
int swap[N][N];
int degree[N], result[N], rank[N];

bool check() {
	for (int i = 1; i <= n; ++i) {
		degree[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < (int)edge[i].size(); ++j) {
			degree[edge[i][j]]++;
		}
	}
	std::vector<int> queue;
	for (int i = 1; i <= n; ++i) {
		if (degree[i] == 0) {
			queue.push_back(i);
		}
	}
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (--degree[y] == 0) {
				queue.push_back(y);
			}
		}
	}
	if ((int)queue.size() < n) {
		return false;
	}
	for (int i = 1; i <= n; ++i) {
		result[i] = queue[i - 1];
	}
	return true;
}

void solve(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int number;
		scanf("%d", &number);
		rank[number] = i;
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			swap[i][j] = 0;
		}
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		swap[a][b] = swap[b][a] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		edge[i].clear();
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j) {
			if (!swap[i][j]) {
				if (rank[i] < rank[j]) {
					edge[i].push_back(j);
				} else {
					edge[j].push_back(i);
				}
			} else {
				if (rank[i] < rank[j]) {
					edge[j].push_back(i);
				} else {
					edge[i].push_back(j);
				}
			}
		}
	}
	if (check()) {
		for (int i = 1; i <= n; ++i) {
			printf("%d%s", result[i], (i == n) ? "\n" : " ");
		}
	} else {
		puts("IMPOSSIBLE");
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
