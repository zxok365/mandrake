#include <cstdio>
#include <vector>

const int N = 1111;

int n, m;
char grid[N][N];
int height[N][N];
int counter[N + N];

void solve(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", grid[i] + 1);
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (grid[i][j] == '.') {
				height[i][j] = height[i - 1][j] + 1;
			} else {
				height[i][j] = 0;
			}
		}
	}
	for (int i = 1; i <= n + m + 1; ++i) {
		counter[i] = 0;
	}
	for (int i = 1; i <= n; ++i) {
		std::vector<std::pair<int, int> > stack;
		for (int j = 1; j <= m; ++j) {
			int best = j;
			for (; !stack.empty() && stack.back().second > height[i][j]; stack.pop_back()) {
				best = std::min(best, stack.back().first);
			}
			if (grid[i][j] == '.') {
				if (stack.empty() || -best + height[i][j] > -stack.back().first + stack.back().second) {
					stack.push_back(std::make_pair(best, height[i][j])); 
				}
				counter[j - stack.back().first + 1 + stack.back().second]++;
			}
		}
	}
	for (int i = 1; i <= n + m + 1; ++i) {
		if (counter[i]) {
			printf("%d x %d\n", counter[i], i * 2);
		}
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
