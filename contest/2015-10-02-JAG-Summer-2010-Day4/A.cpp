#include <cstdio>
#include <algorithm>
#include <vector>

const long long mod = 1000000007;

const int N = 11111;

int n, m;
int edge[N], delta[N];
long long length[N];
bool visit[N];

int main(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		edge[x] = y;
		delta[x]--;
		delta[y]++;
	}
	
	for (int i = 1; i <= n; ++i) {
		if (!edge[i]) {
			edge[i] = i;
		}
		length[i] = 1;
		delta[i]++;
	}
	
	std::vector<int> queue;
	for (int i = 1; i <= n; ++i) {
		if (delta[i] == 0) {
			queue.push_back(i);
		}
	}
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		int y = edge[x];
		(length[y] *= length[x] + 1) %= mod;
		
		if ((--delta[y]) == 0) {
			queue.push_back(y);
		}
	}
	
	long long answer = 1;
	for (int i = 1; i <= n; ++i) {
		if (!visit[i] && delta[i]) {
			long long counter = 1;
			for (int j = i; !visit[j]; j = edge[j]) {
				visit[j] = true;
				(counter *= length[j]) %= mod;
			}
			(answer *= counter + 1) %= mod;
		}
	}
	
	printf("%d\n", (int)answer);
}
