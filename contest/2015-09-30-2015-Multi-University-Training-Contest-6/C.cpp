#include <cstdio>
#include <algorithm>
#include <cassert>
#include <vector>

const int N = 111111;
const int M = 22;

int n, m;
long long rest[M];
std::vector<int> box[M];
int belong[N];

void print(bool flag) {
	if (flag) {
		puts("YES");
		for (int i = 0; i < m; ++i) {
			box[i].clear();
		}
		for (int i = 1; i <= n; ++i) {
			box[belong[i]].push_back(i);
		}
		for (int i = 0; i < m; ++i) {
			printf("%d", (int)box[i].size());
			for (int j = 0; j < (int)box[i].size(); ++j) {
				printf(" %d", box[i][j]);
			}
			puts("");
		}
	} else {
		puts("NO");
	}
}

bool dfs(int dep) {
	if (dep == 0) {
		return true;
	}
	for (int i = 0; i < m; ++i) {
		if (rest[i] >= dep) {
			belong[dep] = i;
			rest[i] -= dep;
			
			if (dfs(dep - 1)) {
				return true;
			}
			
			belong[dep] = 0;
			rest[i] += dep;
		}
	}
	return false;
}

void solve(void) {
	scanf("%d%d", &n, &m);
	
	long long total = 1LL * n * (n + 1) / 2;

	if (total % m != 0 || n < m * 2 - 1) {
		print(0);
		return;
	}

	for (int i = 0; i < m; ++i) {
		rest[i] = total / m;
	}

	int left = n;
	
	while (left > 40) {
		for (int i = 0; i < m; ++i) {
			belong[left - i] = belong[left - m * 2 + i + 1] = i;
			rest[i] -= left * 2 - m * 2 + 1;
		}
		left -= m * 2;
	}

	assert(dfs(left));
	print(1);
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
