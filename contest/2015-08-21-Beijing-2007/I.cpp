#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

const int N = 222;

int n, d;
unsigned long long k;
unsigned long long ways[N][N];
int pos[2][N], counter[N], number[N][2];

void solve(void) {
	std::cin >> d >> k;

	counter[0] = counter[1] = 0;
	for (int i = n - 1; i >= 0; --i) {
		int digit = k >> i & 1;
		pos[digit][++counter[digit]] = n - i - 1;
	}
	
	for (int i = 0; i <= counter[0]; ++i) {
		for (int j = 0; j <= counter[1]; ++j) {
			ways[i][j] = 0;
		}
	}
	
	ways[counter[0]][counter[1]] = 1;
	for (int i = counter[0]; i >= 0; --i) {
		for (int j = counter[1]; j >= 0; --j) {
			if (i == counter[0] && j == counter[1]) {
				continue;
			}
			int index = std::max(pos[0][i], pos[1][j]);
			if (i < counter[0] && pos[0][i + 1] + d >= index) {
				ways[i][j] += ways[i + 1][j];
			}
			if (j < counter[1] && pos[1][j + 1] + d >= index) {
				ways[i][j] += ways[i][j + 1];
			}
		}
	}
	std::cout << ways[0][0] << " ";
	
	{
		for (int i = 0; i < n; ++i) {
			int digit = k >> (n - i - 1) & 1;
			if (digit == 0) {
				number[i + 1][digit]++;
			} else {
				number[i + d + 1][digit]++;
			}
		}
		unsigned long long answer = 0;
		for (int i = 0; i <= n + n; ++i) {
			while (number[i][0] > 0) {
				answer = answer << 1;
				number[i][0]--;
			}
			while (number[i][1] > 0) {
				answer = answer << 1 | 1;
				number[i][1]--;
			}
		}
		std::cout << answer << " ";
	}
	{
		for (int i = 0; i < n; ++i) {
			int digit = k >> (n - i - 1) & 1;
			if (digit == 1) {
				number[i + 1][digit]++;
			} else {
				number[i + d + 1][digit]++;
			}
		}
		unsigned long long answer = 0;
		for (int i = 0; i <= n + n; ++i) {
			while (number[i][1] > 0) {
				answer = answer << 1 | 1;
				number[i][1]--;
			}
			while (number[i][0] > 0) {
				answer = answer << 1;
				number[i][0]--;
			}
		}
		std::cout << answer << std::endl;
	}
}

int main(void) {
	std::ios::sync_with_stdio(false);
	for (int tests = 1; std::cin >> n && n; ++tests) {
		std::cout << "Case " << tests << ": ";
		solve();
	}
}
