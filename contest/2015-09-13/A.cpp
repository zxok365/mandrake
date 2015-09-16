#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

const int N = 222222;

int k, m, q;
char name[N][222];
int val[N], answer[N];
std::pair<int, int> event[N];

void solve(void) {
	scanf("%d%d%d", &k, &m, &q);
	for (int i = 1; i <= k; ++i) {
		scanf("%s%d", name[i], &val[i]);
	}
	for (int i = 0; i < m; ++i) {
		scanf("%d%d", &event[i].first, &event[i].second);
	}
	event[m++] = std::make_pair(k, k);
	std::sort(event, event + m);
	
	std::priority_queue<std::pair<int, int> > heap;
	for (int i = 0, pos = 0, size = 0; i < m; ++i) {
		while (pos < event[i].first) {
			pos++;
			heap.push(std::make_pair(val[pos], -pos));
		}
		for (int j = 0; j < event[i].second && !heap.empty(); ++j) {
			answer[++size] = -heap.top().second;
			heap.pop();
		}
	}
	
	for (int i = 1; i <= q; ++i) {
		int x;
		scanf("%d", &x);
		printf("%s%s", name[answer[x]], (i == q ? "\n" : " "));
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
