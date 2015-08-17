#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cassert>
#include <queue>

const int N = 5555;

int n, m;
std::vector<int> edge[N];
int removed[N], degree[N];

bool check() {
	for (int i = 1; i <= n; ++i) {
		if (!removed[i] && degree[i] != n / 3 - 1) {
			return false;
		}
	}
	return true;
}

int main(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	for (int i = 1; i <= n; ++i) {
		degree[i] = (int)edge[i].size();
	}
	for (int repeat = 0; repeat < n / 3 * 2; ++repeat) {
		int index = -1;
		for (int i = 1; i <= n; ++i) {
			if (removed[i]) {
				continue;
			}
			if (index == -1 || degree[i] < degree[index]) {
				index = i;
			}
		}
		removed[index] = true;
		for (int i = 0; i < (int)edge[index].size(); ++i) {
			int x = edge[index][i];
			degree[x]--;
		}
	}
	if (!check()) {
		do {
			for (int i = 1; i <= n; ++i) {
				degree[i] = (int)edge[i].size();
			}
			for (int repeat = 0; repeat < n / 3 * 2; ++repeat) {
				int index;
				while (true) {
					index = rand() % n + 1;
					if (!removed[index]) {
						break;
					}
				}
				removed[index] = true;
				for (int i = 0; i < (int)edge[index].size(); ++i) {
					int x = edge[index][i];
					degree[x]--;
				}
			}
		} while (!check());
	}
	std::vector<int> answer;
	for (int i = 1; i <= n; ++i) {
		if (!removed[i]) {
			answer.push_back(i);
		}
	}
	for (int i = 0; i < (int)answer.size(); ++i) {
		printf("%d%s", answer[i], (i == (int)answer.size() - 1) ? "\n" : " ");
	}
}
