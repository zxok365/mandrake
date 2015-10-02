#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;
const int N = 111111;
struct edge{
	int u, v, dist;
};

int n, m;
int px[N], py[N], fa[N];

int sqr(int x) {
	return x * x;
}

int getfa(int x) {
	return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}

void mergy(int x, int y) {
	int fx = getfa(x);
	int fy = getfa(y);
	if (fx != fy) {
		fa[fx] = fy;
	}
}

bool cmp(edge e1, edge e2) {
	return e1.dist > e2.dist;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &px[i], &py[i]);
	}
	
	double sum = 0;
	vector<edge> e;
	for (int i = 1; i <= m; i++) {
		int u, v;
		edge tmp;
		scanf("%d%d", &u, &v);
		tmp.u = u; tmp.v = v;
		tmp.dist = sqr(px[u] - px[v]) + sqr(py[u] - py[v]);
		e.push_back(tmp);
		sum += sqrt(1. * tmp.dist);
	}	
	
	sort(e.begin(), e.end(), cmp);
	
	int rest = n;
	for (int i = 1; i <= n; i++) fa[i] = i;
	
	for (int i = 0; i < m; i++) {
		int u = e[i].u, v = e[i].v;
		if (getfa(u) != getfa(v)) {
			mergy(u, v);
			rest--;
			sum -= sqrt(e[i].dist);
		}
		if (rest == 1) break;
	}
	
	printf("%.5f\n", sum);
	return 0;
}
