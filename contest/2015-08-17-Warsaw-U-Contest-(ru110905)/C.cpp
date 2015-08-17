#include <cstdio>
#include <algorithm>
#include <cassert>
#include <queue>
#include <set>
#include <map>

const int N = 555555 * 3;

int n, m;
int a[N], b[N], removed[N], visit[N];
std::set<std::pair<int, int> > edge[N];
std::vector<int> graph[N];
std::queue<int> queue;

void insert(int x) {
	if (!visit[x] && (int)edge[x].size() == 2) {
		visit[x] = true;
		queue.push(x);
	}
}

int findEdge(int x, int y) {
	std::set<std::pair<int, int> >::iterator iterator = edge[x].lower_bound(std::make_pair(y, 0));
	if (iterator != edge[x].end() && iterator->first == y) {
		return iterator->second;
	} else {
		return -1;
	}
}

void addEdge(int i) {
	edge[a[i]].insert(std::make_pair(b[i], i));
	edge[b[i]].insert(std::make_pair(a[i], i));
}

void removeEdge(int i) {
	edge[a[i]].erase(std::make_pair(b[i], i));
	edge[b[i]].erase(std::make_pair(a[i], i));
}
	
int main(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d", a + i, b + i);
		addEdge(i);
	}
	for (int i = 1; i <= n; ++i) {
		insert(i);
	}
	int now = m, rest = n;
	while (!queue.empty()) {
		int x = queue.front();
		queue.pop();
		
		if (edge[x].size() != 2 || rest-- <= 3) {
			continue;
		}
		
		int y, z;
		{
			std::set<std::pair<int, int> >::iterator iterator = edge[x].begin();
			y = iterator->first;
			removeEdge(iterator->second);
		}
		{
			std::set<std::pair<int, int> >::iterator iterator = edge[x].begin();
			z = iterator->first;
			removeEdge(iterator->second);
		}
		
		int index = findEdge(y, z);
		if (index != -1) {
			removed[index] = true;
		} else {
			now++;
			a[now] = y;
			b[now] = z;
			addEdge(now);
		}
		
		insert(y);
		insert(z);
	}

	for (int i = 1; i <= m; ++i) {
		if (!removed[i]) {
			graph[a[i]].push_back(b[i]);
			graph[b[i]].push_back(a[i]);
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		assert((int)graph[i].size() == 2);
	}
	
	std::fill(visit + 1, visit + n + 1, 0);	
	
	visit[1] = true;
	putchar('1');
	
	int pos = std::min(graph[1][0], graph[1][1]);
	
	while (true) {
		visit[pos] = true;
		printf(" %d", pos);
		
		int next = -1;
		for (int i = 0; i < (int)graph[pos].size(); ++i) {
			int x = graph[pos][i];
			if (!visit[x]) {
				next = x;
				break;
			}
		}
		if (next == -1) {
			break;
		}
		pos = next;
	}
	puts("");
}
