#include <cstdio>
#include <algorithm>

const int N = 222222;

int n, m, q, number;
std::pair<int, std::pair<int, int> > edge[N];
std::pair<int, int> query[N];
int father[N], size[N], answer[N];

int calc(int x) {
	return x * (x - 1);
}

int find(int x) {
	if (father[x] != x) {
		father[x] = find(father[x]);
	}
	return father[x];
}

void merge(int x, int y) {
	x = find(x);
	y = find(y);
	if (x != y) {
		number -= calc(size[x]);
		number -= calc(size[y]);
		number += calc(size[x] + size[y]);
		father[x] = y;
		size[y] += size[x];
	}
}

void solve(void) {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < m; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		edge[i] = std::make_pair(w, std::make_pair(x, y));
	}
	std::sort(edge, edge + m);
	for (int i = 0; i < q; ++i) {
		scanf("%d", &query[i].first);
		query[i].second = i;
	}
	sort(query, query + q);
	
	number = 0;
	for (int i = 1; i <= n; ++i) {
		father[i] = i;
		size[i] = 1;
		number += calc(size[i]);
	}
	for (int i = 0, pos = 0; i < q; ++i) {
		while (pos < m && edge[pos].first <= query[i].first) {
			merge(edge[pos].second.first, edge[pos].second.second);
			pos++;
		}
		answer[query[i].second] = number;
	}
	for (int i = 0; i < q; ++i) {
		printf("%d\n", answer[i]);
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
