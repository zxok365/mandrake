#include <cstdio>
#include <algorithm>

const int N = 1111;

int n, start;
std::pair<int, int> a[N];
std::pair<int, int> best[N][N];

__inline std::pair<int, int> operator + (const std::pair<int, int> &a, const std::pair<int, int> &b) {
	return std::make_pair(a.first + b.first, a.second + b.second);
}

std::pair<int, int> dfs(int turn, int jan) {
	if (~best[turn][jan].first) {
		return best[turn][jan];
	}
	std::pair<int, int> &result = best[turn][jan];
	if (turn == n) {
		return result = std::make_pair(0, 0);
	}
	int petya = turn - jan;
	if (turn - jan == (n + start >> 1)) {
		result = dfs(turn + 1, jan + 1) + std::make_pair(-a[turn].second, 0);
	} else {
		result = dfs(turn + 1, jan) + std::make_pair(0, a[turn].first);
		if (jan + start <= petya) {
			result = std::max(result, dfs(turn + 1, jan + 1) + std::make_pair(-a[turn].second, 0));
		}
	}
	return result;
}

void solve(void) {
	static char text[11];
	scanf("%d%s", &n, text);
	
	start = (*text == 'P');
	for (int i = 0; i < n; ++i) {
		int petra, jan;
		scanf("%d%d", &petra, &jan);
		a[i] = std::make_pair(petra, -jan);
	}
	
	std::sort(a, a + n);
	std::reverse(a, a + n);
	
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			best[i][j] = std::make_pair(-1, -1);
		}
	}
	
	std::pair<int, int> answer = dfs(0, 0);
	printf("%d %d\n", answer.second, answer.first);
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
