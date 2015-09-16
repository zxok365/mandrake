#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

const int N = 111111;

int n, m;
std::vector<int> edge[N];
int degree[N], val[N];
bool removed[N], visit[N];

int size;
long long sum;

void dfs(int x) {
	size++;
	sum += val[x];
	visit[x] = true;
	for (int i = 0; i < (int)edge[x].size(); ++i) {
		int y = edge[x][i];
		if (removed[y] || visit[y]) {
			continue;
		}
		dfs(y);
	}
}

void solve(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i) {
		edge[i].clear();
		visit[i] = false;
		removed[i] = false;
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &val[i]);
	}
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x].push_back(y);
		edge[y].push_back(x);
	}
	for (int i = 1; i <= n; ++i) {
		degree[i] = (int)edge[i].size();
	}
	std::vector<int> queue;
	for (int i = 1; i <= n; ++i) {
		if (degree[i] < 2) {
			removed[i] = true;
			queue.push_back(i);
		}
	}
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (!removed[y] && (--degree[y]) < 2) {
				removed[y] = true;
				queue.push_back(y);
			}
		}
	}
	long long answer = 0;
	for (int i = 1; i <= n; ++i) {
		if (visit[i] || removed[i]) {
			continue;
		}
		sum = size = 0;
		dfs(i);
		if (size & 1) {
			answer += sum;
		}
	}
	std::cout << answer << std::endl;
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
