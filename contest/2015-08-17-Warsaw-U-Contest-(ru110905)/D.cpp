#include <cstdio>
#include <vector>
#include <queue>
#include <climits>

const int INF = 1 << 29;

const int N = 555555;

int n, m, q;
std::vector<int> edge[N];
int a[N], b[N];
int number[N], removed[N], answer[N], dist[N];
char type[N];

void spread(int source) {
	static std::queue<int> queue;
	queue.push(source);
	while (!queue.empty()) {
		int x = queue.front();
		queue.pop();
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (dist[y] > dist[x] + 1) {
				dist[y] = dist[x] + 1;
				queue.push(y);
			}
		}
	}
}

int main(void) {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", a + i, b + i);
	}
	for (int i = 1; i <= q; ++i) {
		static char text[11];
		scanf("%s%d", text, &number[i]);
		type[i] = *text;
		if (type[i] == 'U') {
			removed[number[i]] = true;
		}
	}
	for (int i = 1; i <= q; ++i) {
		if (!removed[i]) {
			edge[a[i]].push_back(b[i]);
		}
	}
	for (int i = 1; i <= n; ++i) {
		dist[i] = INF;
	}
	dist[1] = 0;
	spread(1);
	for (int i = q; i >= 1; --i) {
		if (type[i] == 'U') {
			int x = a[number[i]], y = b[number[i]];
			edge[x].push_back(y);
			if (dist[y] > dist[x] + 1) {
				dist[y] = dist[x] + 1;
				spread(y);
			}
		} else {
			int x = number[i];
			if (dist[x] == INF) {
				answer[i] = -1;
			} else {
				answer[i] = dist[x];
			}
		}
	}
	for (int i = 1; i <= q; ++i) {
		if (type[i] == 'E') {
			printf("%d\n", answer[i]);
		}
	}
}
