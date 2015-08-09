#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

const int N = 1111111;

int n;
long long dist[N], physical[N];
std::vector<int> edge[N];

void solve() {
	std::priority_queue<std::pair<long long, int> > heap;
	for (int i = 1; i <= n; i++) {
		heap.push(std::make_pair(-physical[i], i));
	}
	
	while (!heap.empty()) {
		long long _dist = -heap.top().first;
		int x = heap.top().second;
		heap.pop();
		
		if (dist[x] <= _dist) {
			continue;
		}
		
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			physical[y] -= dist[x];
			physical[y] += _dist;
			heap.push(std::make_pair(-physical[y], y));
		}
		
		dist[x] = _dist;
	}
	
	printf("%lld\n", dist[1]);
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld", &physical[i], &dist[i]);
		int counter;
		for (scanf("%d", &counter); counter--; ) {
			int number;
			scanf("%d", &number);
			edge[number].push_back(i);
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < (int)edge[i].size(); ++j) {
			int x = edge[i][j];
			physical[x] += dist[i];
		}
	}
	solve();
}
