namespace maximum_flow {

const int N = , M = ;

struct EdgeList {
	int size;
	int last[N];
	int succ[M], other[M], flow[M];
	void clear(int n) {
		size = 0;
		fill(last, last + n, -1);
	}
	void add(int x, int y, int c) {
		succ[size] = last[x];
		last[x] = size;
		other[size] = y;
		flow[size++] = c;
	}
} e;

int n, source, target;
int dist[N], curr[N];

void add(int x, int y, int c) {
	e.add(x, y, c);
	e.add(y, x, 0);
}

bool bfs() {
	vector<int> queue;
	for (int i = 0; i < n; ++i) {
		curr[i] = e.last[i];
		dist[i] = -1;
	}
	queue.push_back(target);
	dist[target] = 0;
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = e.last[x]; ~i; i = e.succ[i]) {
			int y = e.other[i];
			if (e.flow[i ^ 1] && dist[y] == -1) {
				dist[y] = dist[x] + 1;
				queue.push_back(y);
			}
		}
	}
	return ~dist[source];
}

int dfs(int x, int ans) {
	if (x == target) {
		return ans;
	}
	int delta = ans;
	for (int &i = curr[x]; ~i; i = e.succ[i]) {
		int y = e.other[i];
		if (e.flow[i] && dist[x] == dist[y] + 1) {
			int num = dfs(y, min(e.flow[i], delta));
			e.flow[i] -= num;
			e.flow[i ^ 1] += num;
			if ((delta -= num) == 0) {
				break;
			}
		}
	}
	return ans - delta;
}

int solve() {
	int ans = 0;
	for (; bfs(); ans += dfs(source, INT_MAX));
	return ans;
}

void clear() {
	e.clear(n);
}

}
