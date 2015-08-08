#include <cstdio>
#include <vector>
#include <algorithm>

const int N = 555;

int n;
char map[N][N];
int row[N], column[N];
std::vector<std::pair<char, int> > answer;

bool finish() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (map[i][j] != '.') {
				return false;
			}
		}
	}
	return true;
}

bool find_row() {
	for (int i = n - 1; i >= 0; --i) {
		if (row[i]) {
			continue;
		}
		bool flag = true;
		for (int j = 0; j < n; ++j) {
			if (map[i][j] == 'O') {
				flag = false;
				break;
			}
		}
		if (flag) {
			row[i] = true;
			for (int j = 0; j < n; ++j) {
				map[i][j] = '.';
			}
			answer.push_back(std::make_pair('R', i));
			return true;
		}
	}
	return false;
}

bool find_column() {
	for (int j = n - 1; j >= 0; --j) {
		if (column[j]) {
			continue;
		}
		bool flag = true;
		for (int i = 0; i < n; ++i) {
			if (map[i][j] == 'X') {
				flag = false;
				break;
			}
		}
		if (flag) {
			column[j] = true;
			for (int i = 0; i < n; ++i) {
				map[i][j] = '.';
			}
			answer.push_back(std::make_pair('C', j));
			return true;
		}
	}
	return false;
}

void solve(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%s", map[i]);
	}
	answer.clear();
	std::fill(row, row + n, 0);
	std::fill(column, column + n, 0);
	while (!finish()) {
		if (find_row()) {
			continue;
		}
		if (find_column()) {
			continue;
		}
		puts("No solution");
		return;
	}
	std::reverse(answer.begin(), answer.end());
	for (int i = 0; i < (int)answer.size(); ++i) {
		printf("%c%d%s", answer[i].first, answer[i].second + 1, (i == (int)answer.size() - 1) ? "\n" : " ");
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
