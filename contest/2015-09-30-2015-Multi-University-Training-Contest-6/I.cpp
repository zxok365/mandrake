#include <cstdio>
#include <algorithm>
#include <climits>
#include <queue>

const long long INF = 1LL << 60;

const int mark[] = {1, -1};

const int N = 444444;

int n;
int l[N], r[N], d[N];
int father[N];
long long dist[N];

__inline int find(int x) {
	int root = x;
	while (father[root] != root) {
		root = father[root];
	}
	while (father[x] != x) {
		int y = father[x];
		father[x] = root;
		x = y;
	}
	return root;
}

__inline void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		father[x] = y;
	}
}

void solve(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", l + i);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", r + i);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", d + i);
	}
	
	for (int i = 1; i <= n + n; ++i) {
		father[i] = i;
	}
	
	std::priority_queue<std::pair<std::pair<long long, long long>, int> > heap;
	
	for (int i = 1; i <= n; ++i) {
		dist[i] = INF;
	}
	
	dist[1] = 0;
	heap.push(std::make_pair(std::make_pair(-dist[1] - d[1], -dist[1]), 1));
	merge(1, 2);
	
	while (!heap.empty()) {
		int x = heap.top().second;
		heap.pop();

		for (int sign = 0; sign < 2; ++sign) {
			int left = x + mark[sign] * l[x];
			int right = x + mark[sign] * r[x];
			
			if (left > right) {
				std::swap(left, right);
			}
			
			for (int y = std::max(left, 1); ; y++) {
				y = find(y);
				if (y > right || y > n) {
					break;
				}
				if (dist[y] > dist[x] + d[x]) {
					dist[y] = dist[x] + d[x];
					heap.push(std::make_pair(std::make_pair(-dist[y] - d[y], -dist[y]), y));
					merge(y, y + 1);
				}
			}
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		if (dist[i] == INF) {
			dist[i] = -1;
		}
		printf("%lld%s", dist[i], (i == n) ? "\n" : " ");
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
