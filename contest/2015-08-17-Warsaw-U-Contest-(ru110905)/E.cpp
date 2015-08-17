#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 1111111;

int n;
std::vector<int> edge[N];
int depth[N], belong[N], number[N], size[N];

void bfs(int source) {
	std::vector<int> queue;
	std::fill(depth, depth + n, -1);
	
	queue.push_back(source);
	depth[source] = 0;
	
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (depth[y] == -1) {
				depth[y] = depth[x] + 1;
				queue.push_back(y);
			}
		}
	}
	
	for (int head = n - 1; head >= 0; --head) {
		int x = queue[head];
		
		size[x] = 1;
		number[x] = 0;
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (depth[y] == depth[x] + 1) {
				size[x] += size[y];
				number[x] = std::max(number[x], size[y]);
			}
		}
		number[x] = std::max(number[x], n - size[x]);
	}
	
	std::fill(belong, belong + n, -1);
	
	for (int index = 0; index < (int)edge[source].size(); ++index) {
		int root = edge[source][index];
		
		std::vector<int> queue;
		
		queue.push_back(root);
		belong[root] = root;
		for (int head = 0; head < (int)queue.size(); ++head) {
			int x = queue[head];
			for (int i = 0; i < (int)edge[x].size(); ++i) {
				int y = edge[x][i];
				if (depth[y] == depth[x] + 1) {
					belong[y] = belong[x];
					queue.push_back(y);
				}
			}
		}
	}
}

int main(void) {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x - 1].push_back(y - 1);
		edge[y - 1].push_back(x - 1);
	}
	
/*	bfs(1);
	for (int i = 0; i < n; ++i) {
		printf("%d %d\n", i + 1, depth[i]);
	}
	
	return 0;
*/	bfs(0);
	for (int x = 0; x < n; ++x) {
		if (number[x] > (n >> 1)) {
			puts("-1");
		} else {
			bfs(x);

			long long answer = 0;
			for (int i = 0; i < n; ++i) {
				answer += (depth[i] << 1);
			}
			
			int component = -1;
			if (number[x] == (n >> 1)) {
				for (int i = 0; i < (int)edge[x].size(); ++i) {
					int y = edge[x][i];
					if (size[y] == number[x]) {
						component = y;
						break;
					}
				}
			}
			
			long long length = 0;
			for (int i = 0; i < n; ++i) {
				if (component == -1 || component == belong[i]) {
					length = std::max(length, (long long)depth[i]);
				}
			}
			
			printf("%lld\n", answer - length);
		}
	}
}
