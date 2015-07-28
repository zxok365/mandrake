#include <cstdio>
#include <climits>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const long long INF = 1LL << 60;

const int N = 222;
const int M = 5555;

struct EdgeList {
	int size;
	int last[N];
	int succ[M], other[M], cost[M], limit[M];
	
	void clear(int n) {
		size = 0;
		fill(last, last + n, -1);
	}
	
	void add(int x, int y, int w, int c) {
		succ[size] = last[x];
		other[size] = y;
		cost[size] = w;
		limit[size] = c;
		last[x] = size++;
	}
} e;

int n, m, k, t;
long long graph[N][N];

struct Node {
	int index;
	long long dist;
	
	Node() {}
	Node(int index, const long long &dist) : index(index), dist(dist) {}
	
	long long value() const {
		return dist + graph[index][n - 1];
	}
	
	friend bool operator < (const Node &a, const Node &b) {
		if (a.value() != b.value()) {
			return a.value() > b.value();
		} else {
			return a.index < b.index;
		}
	}
};

void solve(void) {
	k++;
	
	e.clear(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			graph[i][j] = INF;
		}
		graph[i][i] = 0;
	}
	
	for (int i = 0; i < m; ++i) {
		int x, y, w, c;
		scanf("%d%d%d%d", &x, &y, &c, &w);
		e.add(x, y, w, c);
		graph[x][y] = min(graph[x][y], 1LL * w);
	}
	
	for (int l = 0; l < n; ++l) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				graph[i][j] = min(graph[i][j], graph[i][l] + graph[l][j]);
			}
		}
	}
	
	vector<long long> ans;
	priority_queue<Node> heap;
	map<Node, int> counter;

	heap.push(Node(0, 0LL));
	counter[Node(0, 0LL)] = 1;

	for (; !heap.empty(); ) {
		Node x = heap.top();
		heap.pop();

		if (x.index == n - 1) {
			for (int i = 0; i < counter[x]; ++i) {
				ans.push_back(x.dist);
			}
		}
		if ((int)ans.size() >= k) {
			break;
		}

		for (int i = e.last[x.index]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			for (long long wait = 0; wait <= t; ++wait) {
				if ((x.dist + wait) % e.limit[i] == 0) {
					Node w = Node(y, x.dist + wait + e.cost[i]);
					if (counter[w] == 0) {
						heap.push(w);
					}
					counter[w] = min(counter[w] + counter[x], k);
				}
			}
		}
		counter[x] = 0;
	}
	
	if ((int)ans.size() < k) {
		puts("-1");
	} else {
		printf("%lld\n", ans[k - 1]);
	}
}

int main(void) {
	for (int tests = 1; ~scanf("%d%d%d%d", &n, &m, &k, &t) && (n || m || k || t); ++tests) {
		printf("Case %d: ", tests);
		solve();
	}
}
