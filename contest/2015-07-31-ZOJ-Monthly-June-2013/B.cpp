#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

const double eps = 1e-5;

const int N = 2222;

class Point {
public:
	double x, y, z;
	
	void read() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
};

__inline double sqr(const double &x) {
	return x * x;
}

__inline double dist(const Point &a, const Point &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z));
}

int n, times, comps, top;
vector<int> adj[N];
int dfn[N], low[N], comp[N], stack[N];
Point a[N];

void tarjan(int x) {
	dfn[x] = low[x] = ++times;
	stack[top++] = x;
	for (int i = 0; i < (int)adj[x].size(); ++i) {
		int y = adj[x][i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = min(low[x], low[y]);
		} else if (!comp[y]) {
			low[x] = min(low[x], dfn[y]);
		}
	}
	if (low[x] == dfn[x]) {
		comps++;
		do {
			int y = stack[--top];
			comp[y] = comps;
		} while (stack[top] != x);
	}
}

bool check(const double &radius) {
	for (int i = 2; i <= n + n + 1; ++i) {
		adj[i].clear();
	}
	for (int i = 2; i <= n + n + 1; ++i) {
		for (int j = i + 1; j <= n + n + 1; ++j) {
			if (dist(a[i], a[j]) < radius * 2) {
				adj[i].push_back(j ^ 1);
				adj[j].push_back(i ^ 1);
			}
		}
	}
	
	times = top = comps = 0;
	fill(dfn + 1, dfn + (n + n + 1) + 1, 0);
	fill(comp + 1, comp + (n + n + 1) + 1, 0);
	for (int i = 2; i <= (n + n + 1); ++i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (comp[i + i] == comp[i + i + 1]) {
			return false;
		}
	}
	return true;
}

void solve(void) {
	for (int i = 1; i <= n; ++i) {
		a[i + i].read();
		a[i + i + 1].read();
	}
	
	double left = 0, right = 1e6;
	for (; fabs(right - left) > eps; ) {
		double mid = (left + right) / 2;
		if (check(mid)) {
			left = mid;
		} else {
			right = mid;
		}
	}
	
	double result = (left + right) / 2;
	
	printf("%.3f\n", (int)(result * 1000) / 1000.);
}

int main(void) {
	for (; ~scanf("%d", &n); solve());
}
