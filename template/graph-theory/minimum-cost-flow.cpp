struct EdgeList {
	int size;
	int last[N];
	int succ[M], other[M], flow[M], cost[M];
	
	void clear(int n) {
		size = 1;
		std::fill(last + 1, last + n + 1, 0);
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

int n, m, source, target;
int prev[N];

void add(int x, int y, int c, int w) {
	e.add(x, y, c, w);
	e.add(y, x, 0, -w);
}

bool spfa() {
	static int dist[N];
	static bool exist[N];
	std::vector<int> queue;
	std::fill(dist + 1, dist + n + 1, INT_MAX);
	std::fill(exist + 1, exist + n + 1, 0);
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

std::pair<int, int> solve() {
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
	return std::make_pair(flow, cost);
}