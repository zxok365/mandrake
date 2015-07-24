#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

const int N = 222222;

int n, q, m;

struct Point {
	int x, y, id;
	
	Point() {};
	Point(int x, int y) : x(x), y(y) {}
};

__inline Point operator - (const Point &a, const Point &b) {
	return Point(a.x - b.x, a.y - b.y);
}

__inline long long det(const Point &a, const Point &b) {
	return 1LL * a.x * b.y - 1LL * b.x * a.y;
}

__inline long long dot(const Point &a, const Point &b) {
	return 1LL * a.x * b.x + 1LL * a.y * b.y;
}

__inline long long sqr(int x) {
	return 1LL * x * x;
}

__inline long long dist(const Point &a, const Point &b) {
	return sqr(a.x - b.x) + sqr(a.y - b.y);
}

struct Rectangle {
	int lx, rx, ly, ry;
	void set(const Point &p) {
		lx = rx = p.x;
		ly = ry = p.y;
	}
	void mergy(const Point &p) {
		lx = min(lx, p.x);
		rx = max(rx, p.x);
		ly = min(ly, p.y);
		ry = max(ry, p.y);
	}
	void mergy(const Rectangle &r) {
		lx = min(lx, r.lx);
		rx = max(rx, r.rx);
		ly = min(ly, r.ly);
		ry = max(ry, r.ry);
	}
	long long dist(const Point &p) {
		if (p.x <= lx && p.y <= ly){
			return sqr(p.x - lx) + sqr(p.y - ly);
		}
		if (p.x <= rx && p.y <= ly){
			return sqr(p.y - ly);
		}
		if (p.x >= rx && p.y <= ly){
			return sqr(p.x - rx) + sqr(p.y - ly);
		}
		if (p.x >= rx && p.y <= ry){
			return sqr(p.x - rx);
		}
		if (p.x >= rx && p.y >= ry){
			return sqr(p.x - rx) + sqr(p.y - ry);
		}
		if (p.x >= lx && p.y >= ry){
			return sqr(p.y - ry);
		}
		if (p.x <= lx && p.y >= ry){
			return sqr(p.x - lx) + sqr(p.y - ry);
		}
		if (p.x <= lx && p.y >= ly){
			return sqr(p.x - lx);
		}
		return 0;
	}
};
struct Node{
	int child[2];
	Point p;
	Rectangle r;
	void set(const Point &_p){
		p = _p;
		r.set(p);
		child[0] = child[1] = 0;
	}
};

int size;
Point a[N], b[N];
Node tree[N];

__inline bool xcompare(const Point &a, const Point &b){
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

__inline bool ycompare(const Point &a, const Point &b){
	return a.y < b.y || a.y == b.y && a.x < b.x;
}

__inline int build(int left, int right, bool dim = 0){
	int x = ++size, mid = left + right >> 1;
	nth_element(a + left, a + mid, a + right, dim ? xcompare : ycompare);
	tree[x].set(a[mid]);
	if (left < mid) {
		tree[x].child[0] = build(left, mid, dim ^ 1);
		tree[x].r.mergy(tree[tree[x].child[0]].r);
	}
	if (mid + 1 < right) {
		tree[x].child[1] = build(mid + 1, right, dim ^ 1);
		tree[x].r.mergy(tree[tree[x].child[1]].r);
	}
	return x;
}

void query(int x, const Point &p, int k, pair<long long, int> ret[], bool dim = 0) {
	if (tree[x].r.dist(p) > ret[k].first){
		return;
	}
	pair<long long, int> val = make_pair(dist(tree[x].p, p), tree[x].p.id);
	for (int i = 1; i <= k; ++i) {
		if (val < ret[i]) {
			for (int j = k + 1; j > i; --j) {
				ret[j] = ret[j - 1];
			}
			ret[i] = val;
			break;
		}
	}
	if (dim && xcompare(p, tree[x].p) || !dim && ycompare(p, tree[x].p)) {
		if (tree[x].child[0]) {
			query(tree[x].child[0], p, k, ret, dim ^ 1);
		}
		if (tree[x].child[1]) {
			query(tree[x].child[1], p, k, ret, dim ^ 1);
		}
	} else {
		if (tree[x].child[1]) {
			query(tree[x].child[1], p, k, ret, dim ^ 1);
		}
		if (tree[x].child[0]) {
			query(tree[x].child[0], p, k, ret, dim ^ 1);
		}
	}
}

__inline bool point_on_line(const Point &a, const Point &b, const Point &c) {
	return det(a - b, c - b) == 0 && dot(b - a, c - a) <= 0;
}

__inline bool in_polygon(const Point &p, const vector<Point> &poly) {
	int n = (int)poly.size();
	int counter = 0;
	for (int i = 0; i < n; ++i) {
		Point a = poly[i], b = poly[(i + 1) % n];
		if (point_on_line(p, a, b)) {
			return true;
		}
		long long x = det(p - a, b - a);
		long long y = a.y - p.y;
		long long z = b.y - p.y;
		if (x > 0 && y <= 0 && z > 0) {
			counter++;
		}
		if (x < 0 && z <= 0 && y > 0) {
			counter--;
		}
	}
	return counter != 0;
}

void solve() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &b[i].x, &b[i].y);
		b[i].id = i;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i) {
		printf("Region %d\n", i);
		
		int sum;
		scanf("%d", &sum);
		
		vector<Point> list;
		for (int j = 0; j < sum; ++j) {
			Point p;
			scanf("%d%d", &p.x, &p.y);
			list.push_back(p);
		}
		
		int tot = 0;
		for (int j = 1; j <= n; ++j) {
			if (in_polygon(b[j], list)) {
				a[tot++] = b[j];
			}
		}
		
		size = 0;
		int root = build(0, tot);
		
		scanf("%d", &q);
		for (Point p; q--; ) {
			pair<long long, int> ret[4] = {make_pair(LONG_LONG_MAX, 0), make_pair(LONG_LONG_MAX, 0), make_pair(LONG_LONG_MAX, 0), make_pair(LONG_LONG_MAX, 0)};

			scanf("%d%d", &p.x, &p.y);
			query(root, p, 2, ret);
			printf("%d %d\n", ret[1].second, ret[2].second);
		}
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
