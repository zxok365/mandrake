#include <cstdio>
#include <iostream>
#include <algorithm>
#include <climits>
#include <vector>
#include <cmath>

__inline double sqr(const double &x) {
	return x * x;
}

const int N = 1111;
const int M = 111111;

class EdgeList {
public:
	int size;
	int last[N], succ[M], other[M], flow[M];
	double cost[M];
	
	void clear(int n) {
		size = 0;
		std::fill(last, last + n, -1);
	}
	
	void add(int x, int y, int c, const double &w) {
		succ[size] = last[x];
		other[size] = y;
		flow[size] = c;
		cost[size] = w;
		last[x] = size++;
	}
} e;

void add(int x, int y, int c, const double &w) {
	e.add(x, y, c, w);
	e.add(y, x, 0, -w);
}

int n, x, y;
std::pair<int, int> a[N];
std::vector<int> edge[N];
int prev[N], occur[N], counter[N], visit[N];
double dist[N];

double find() {
	std::vector<int> queue;
	for (int i = 0; i < n; ++i) {
		dist[i] = INT_MIN;
		counter[i] = 0;
		prev[i] = -1;
		occur[i] = false;
		queue.push_back(i);
	}
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (e.flow[i] && dist[y] < dist[x] + e.cost[i]) {
				dist[y] = dist[x] + e.cost[i];
				prev[y] = i;
				if (!occur[y]) {
					occur[y] = true;
					if (++counter[y] > n) {
						std::vector<int> list;
						static int stamp = 0;

						stamp++;
						int pos = y;
						for (; visit[pos] != stamp; pos = e.other[prev[pos] ^ 1]) {
							visit[pos] = stamp;
						}
						
						stamp++;
						for (; visit[pos] != stamp; pos = e.other[prev[pos] ^ 1]) {
							visit[pos] = stamp;
							list.push_back(prev[pos]);
						}
						
						int flow = INT_MAX;
						for (int i = 0; i < (int)list.size(); ++i) {
							flow = std::min(flow, e.flow[list[i]]);
						}

						double answer = 0;
						for (int i = 0; i < (int)list.size(); ++i) {
							e.flow[list[i]] -= flow;
							e.flow[list[i] ^ 1] += flow;
							answer += flow * e.cost[list[i]];
						}
						return answer;
					} else {
						queue.push_back(y);
					}
				}
			}
		}
		occur[x] = false;
	}
	return 0;
}

void solve(void) {
	e.clear(n);
	for (int i = 0; i < n; ++i) {
		edge[i].clear();
	}
	scanf("%d%d", &x, &y);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
		for (int number; scanf("%d", &number) && number; ) {
			edge[i].push_back(number - 1);
		}
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < (int)edge[i].size(); ++j) {
			int k = edge[i][j];
			add(i, k, 1, sqrt(sqr(a[i].first - a[k].first) + sqr(a[i].second - a[k].second)) * x - y);
		}
	}

	double answer = 0;
	while (true) {
		double delta = find();
		answer += delta;
		if (std::abs(delta) < 1e-4) {
			break;
		}
	}
	printf("%.2f\n", answer);
}

int main(void) {
	for (int tests = 1; scanf("%d", &n) && n; ++tests) {
		printf("Case %d: ", tests);
		solve();
	}
}
