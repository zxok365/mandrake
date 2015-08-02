#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

namespace MCF {

const int N = 1111, M = 222222;

struct EdgeList {
	int size;
	int last[N];
	int succ[M], other[M], flow[M], cost[M];
	
	void clear(int n) {
		size = 1;
		fill(last + 1, last + n + 1, 0);
	}
	
	void add(int x, int y, int c, int w) {
		size++;
		succ[size] = last[x];
		last[x] = size;
		other[size] = y;
		flow[size] = c;
		cost[size] = w;
	}
} e;

int n, source, target;
int prev[N];

void add(int x, int y, int c, int w) {
	e.add(x, y, c, w);
	e.add(y, x, 0, -w);
}

bool spfa() {
	static int dist[N];
	static bool exist[N];
	vector<int> queue;
	fill(dist + 1, dist + n + 1, INT_MAX);
	fill(exist + 1, exist + n + 1, 0);
	queue.push_back(source);
	dist[source] = 0;
	exist[source] = true;
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		exist[x] = false;
		for (int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			if (e.flow[i] && dist[y] > dist[x] + e.cost[i]) {
				dist[y] = dist[x] + e.cost[i];
				prev[y] = i;
				if (!exist[y]) {
					exist[y] = true;
					queue.push_back(y);
				}
			}
		}
	}
	return dist[target] < INT_MAX;
}

pair<int, int> solve() {
	int flow = 0, cost = 0;
	for (; spfa(); ) {
		int num = INT_MAX;
		for (int i = target; i != source; i = e.other[prev[i] ^ 1]) {
			num = min(num, e.flow[prev[i]]);
		}
		flow += num;
		for (int i = target; i != source; i = e.other[prev[i] ^ 1]) {
			e.flow[prev[i]] -= num;
			e.flow[prev[i] ^ 1] += num;
			cost += num * e.cost[prev[i]];
		}
	}
	return make_pair(flow, cost);
}

void clear() {
	e.clear(n);
}

}

int n, m;

void solve(void) {
	MCF::n = n + n + 2;
	MCF::source = 1;
	MCF::target = n + n + 2;
	MCF::clear();
	
	for (int i = 1; i <= n; ++i) {
		MCF::add(i + 1, i + n + 1, INT_MAX, 0);
	}
	int suma = 0, sumb = 0;
	for (int i = 1; i <= n; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		MCF::add(MCF::source, i + 1, a, 0);
		MCF::add(i + n + 1, MCF::target, b, 0);
		suma += a;
		sumb += b;
	}
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		MCF::add(x + 1, y + n + 1, INT_MAX, 1);
		MCF::add(y + n + 1, x + 1, INT_MAX, 1);
		MCF::add(y + 1, x + n + 1, INT_MAX, 1);
		MCF::add(x + n + 1, y + 1, INT_MAX, 1);
	}
	if (suma != sumb) {
		puts("-1");
		return;
	}
	pair<int, int> result = MCF::solve();
	if (result.first == suma) {
		printf("%d\n", result.second);
	} else {
		puts("-1");
	}
}	

int main(void) {
	for (; ~scanf("%d%d", &n, &m); solve());
}
