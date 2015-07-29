#include <cstdio>
#include <vector>
#include <climits>

using namespace std;

const int N = 111111;

int n, m;
vector<int> adj[N];
int dist[N], father[N];

int bfs(int source) {
	vector<int> queue;
	fill(dist, dist + n, -1);
	
	queue.push_back(source);
	dist[source] = 0;
	father[source] = -1;
	
	int result = INT_MAX;
	
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)adj[x].size(); ++i) {
			int y = adj[x][i];
			
			if (y == father[x]) {
				continue;
			}
			if (dist[y] == -1) {
				dist[y] = dist[x] + 1;
				father[y] = x;
				queue.push_back(y);
			} else {
				result = min(result, dist[x] + dist[y] + 1);
				if (result == 3) {
					return result;
				}
			}
		}
	}
	
	return result;
}

void solve(void) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		adj[i].clear();
	}
	for (int i = 0; i < m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	int result = INT_MAX;
	for (int i = 0; i < n; ++i) {
		result = min(result, bfs(i));
		if (result == 3) {
			break;
		}
	}
	if (result == INT_MAX) {
		puts("impossible");
	} else {
		printf("%d\n", result);
	}
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case %d: ", i);
		solve();
	}
}
