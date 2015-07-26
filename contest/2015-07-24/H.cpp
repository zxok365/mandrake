#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int N = 111111;

int n, q, w, h;
pair<int, int> a[N];
set<pair<int, int> > data[N << 2];

void insert(int x, int l, int r, int qx, int qy, int id) {
	if (qx < l || r < qx) {
		return;
	}
//printf("data insert %d %d %d\n", x, qy, id);
	data[x].insert(make_pair(qy, id));
	if (qx <= l && r <= qx) {
		return;
	}
	int mid = l + r >> 1;
	insert(x << 1, l, mid, qx, qy, id);
	insert(x << 1 | 1, mid + 1, r, qx, qy, id);
}

void build(int x, int left, int right) {
	data[x].clear();
	if (left < right) {
		int mid = left + right >> 1;
		build(x << 1, left, mid);
		build(x << 1 | 1, mid + 1, right);
	}
}

int find(int x, int l, int r, int ql, int qr, int low, int high) {
	if (qr < l || r < ql) {
		return -1;
	}
	if (ql <= l && r <= qr) {
		set<pair<int, int> >::iterator it = data[x].lower_bound(make_pair(low, -1));
		if (it != data[x].end() && it->first <= high) {
			return it->second;
		} else {
			return -1;
		}
	}
	int mid = l + r >> 1;
	int ret = find(x << 1, l, mid, ql, qr, low, high);
	if (ret != -1) {
		return ret;
	} else {
		return find(x << 1 | 1, mid + 1, r, ql, qr, low, high);
	}
}

void remove(int x, int l, int r, int qx, int qy, int id) {
	if (qx < l || r < qx) {
		return;
	}
	data[x].erase(make_pair(qy, id));
	if (qx <= l && r <= qx) {
		return;
	}
	int mid = l + r >> 1;
	remove(x << 1, l, mid, qx, qy, id);
	remove(x << 1 | 1, mid + 1, r, qx, qy, id);
}

void solve(void) {
	scanf("%d%d%d%d", &n, &q, &w, &h);
	
	build(1, 0, w + h);
	
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].first, &a[i].second);
//printf("insert %d %d\n", a[i].first + a[i].second, a[i].first - a[i].second);
		insert(1, 0, w + h, a[i].first + a[i].second, a[i].first - a[i].second, i);
	}
	
	for (int i = 0; i < q; ++i) {
		int x, y, r, aa, bb, cc, dd, ee, ff;
		scanf("%d%d%d%d%d%d%d%d%d", &x, &y, &r, &aa, &bb, &cc, &dd, &ee, &ff);
		
		int xx = x + y;
		int yy = x - y;
		
		vector<int> list;
		
//printf("find %d %d %d %d\n", max(xx - r, 0), min(xx + r, w + h), yy - r, yy + r);
		
		while (true) {
			int id = find(1, 0, w + h, max(xx - r, 0), min(xx + r, w + h), yy - r, yy + r);
			if (id == -1) {
				break;
			}
			list.push_back(id);

			remove(1, 0, w + h, a[id].first + a[id].second, a[id].first - a[id].second, id);
		}
		
		for (int j = 0; j < (int)list.size(); ++j) {
			int k = list[j];
			pair<int, int> prev = a[k];
			a[k].first = (1LL * prev.first * aa + 1LL * prev.second * bb + 1LL * (k + 1) * cc) % w;
			a[k].second = (1LL * prev.first * dd + 1LL * prev.second * ee + 1LL * (k + 1) * ff) % h;
			insert(1, 0, w + h, a[k].first + a[k].second, a[k].first - a[k].second, k);
		}
	}
	
	for (int i = 0; i < n; ++i) {
		printf("%d %d\n", a[i].first, a[i].second);
	}
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case #%d:\n", i);
		solve();
	}
}


