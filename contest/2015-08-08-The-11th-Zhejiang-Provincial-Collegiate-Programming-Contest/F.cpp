#include <cstdio>
#include <algorithm>
#include <climits>
#include <vector>

const int N = 44;

const int dirx[] = {0, 0, 1, -1};
const int diry[] = {1, -1, 0, 0};

int n, m, counter;
char map[N][N];
int id[N][N], dist[N * N];
std::vector<int> edge[N * N];

void dfs(int x1, int y1) {
	for (int dir = 0; dir < 4; ++dir) {
		int x2 = x1 + dirx[dir];
		int y2 = y1 + diry[dir];
		if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < m) {
			if (map[x1][y1] == map[x2][y2] && id[x2][y2] == -1) {
				id[x2][y2] = id[x1][y1];
				dfs(x2, y2);
			} else if (map[x1][y1] != map[x2][y2] && id[x2][y2] != -1) {
				edge[id[x1][y1]].push_back(id[x2][y2]);
				edge[id[x2][y2]].push_back(id[x1][y1]);
			}
		}
	}
}

int bfs(int source) {
	std::vector<int> queue;
	std::fill(dist, dist + counter, -1);
	queue.push_back(source);
	dist[source] = 0;
	int answer = 0;
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		answer = std::max(answer, dist[x]);
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (dist[y] == -1) {
				dist[y] = dist[x] + 1;
				queue.push_back(y);
			}
		}
	}
	return answer;
}

void solve(void) {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		scanf("%s", map[i]);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			id[i][j] = -1;
		}
	}
	
	counter = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (id[i][j] == -1) {
				edge[counter].clear();
				id[i][j] = counter++;
				dfs(i, j);
			}
		}
	}
	
	int answer = INT_MAX;
	for (int i = 0; i < counter; ++i) {
		answer = std::min(answer, bfs(i));
	}
	printf("%d\n", answer);
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
