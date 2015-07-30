#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const long long INF = 1LL << 60;
const int N = 222222;

struct Event {
	int x, y, id;
	long long w;
	Event() {}
	Event(int x, int y, const long long &w, int id) : x(x), y(y), w(w), id(id) {}
};

__inline bool operator < (const Event &a, const Event &b) {
	if (a.x != b.x) {
		return a.x > b.x;
	} else if (a.y != b.y) {
		return a.y < b.y;
	} else {
		return a.id < b.id;
	}
}

int n, m, q;
long long sum[N], tree[N], ans[N];

__inline int lowbit(int x) {
	return x & -x;
}

void edit(int x, const long long &val) {
	for (int i = x; i <= n; i += lowbit(i)) {
		tree[i] = min(tree[i], val);
	}
}

long long query(int x) {
	long long result = INF;
	for (int i = x; i >= 1; i -= lowbit(i)) {
		result = min(result, tree[i]);
	}
	return result;
}

void solve(void) {
	for (int i = 1; i < n; ++i) {
		int x;
		scanf("%d", &x);
		sum[i + 1] = sum[i] + x;
	}
	
	vector<Event> event;
	for (int i = 1; i <= m; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		event.push_back(Event(x, y, w, 0));
	}
	
	scanf("%d", &q);
	for (int i = 1; i <= q; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		event.push_back(Event(x, y, 0, i));
	}
	
	sort(event.begin(), event.end());
	
	for (int i = 1; i <= n; ++i) {
		tree[i] = INF;
	}
	for (int i = 0; i < (int)event.size(); ++i) {
		if (event[i].x <= event[i].y) {
			if (event[i].id == 0) {
				edit(event[i].y, event[i].w - (sum[event[i].y] - sum[event[i].x]));
			} else {
				ans[event[i].id] = sum[event[i].y] - sum[event[i].x] + min(query(event[i].y), 0LL);
			}
		}
	}
	for (int i = 1; i <= n; ++i) {
		tree[i] = INF;
	}
	for (int i = 0; i < (int)event.size(); ++i) {
		if (event[i].x > event[i].y) {
			if (event[i].id == 0) {
				edit(event[i].y, event[i].w - (sum[event[i].y] - sum[event[i].x]));
			} else {
				ans[event[i].id] = query(event[i].y) + (sum[event[i].y] - sum[event[i].x]);
			}
		}
	}
	
	for (int i = 1; i <= q; ++i) {
		printf("%d\n", (int)ans[i]);
	}
}

int main(void) {
	for (; ~scanf("%d%d", &n, &m); solve());
}
