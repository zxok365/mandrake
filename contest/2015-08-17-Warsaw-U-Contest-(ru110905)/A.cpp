#include <cstdio>
#include <algorithm>
#include <map>

const int N = 33;

int stamp;
int number[2];
int bit[2][N];
std::map<std::pair<int, std::pair<int, int> >, long long> ways;

long long dfs(int i, int a, int b) {
	if (ways.count(std::make_pair(i, std::make_pair(a, b)))) {
		return ways[std::make_pair(i, std::make_pair(a, b))];
	}
	
	long long &result = ways[std::make_pair(i, std::make_pair(a, b))];
	
	if (i == 32) {
		return result = (a == 0 && b == 0);
	}
	
	result = 0;
	for (int mask0 = 0; mask0 < 4; ++mask0) {
		for (int mask1 = 0; mask1 < 4; ++mask1) {
			if (__builtin_popcount(mask0 ^ mask1) == 1) {
				continue;
			}
			int num0 = a + __builtin_popcount(mask0);
			int num1 = b + __builtin_popcount(mask1);
			if ((num0 & 1) == bit[0][i] && (num1 & 1) == bit[1][i]) {
				result += dfs(i + 1, num0 >> 1, num1 >> 1);
			}
		}
	}
	return result;
}

void solve(void) {
	for (int i = 0; i < 2; ++i) {
		scanf("%d", &number[i]);
		number[i]--;
	}
	
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 32; ++j) {
			bit[i][j] = number[i] & 1;
			number[i] >>= 1;
		}
	}
	
	ways.clear();
	printf("%lld\n", dfs(0, 0, 0));
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
