#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

const long double eps = 1e-9;

class Point {
public:
	long double x, y;
	
	Point() {}
	
	Point(const long double &x, const long double &y) : x(x), y(y) {}
	
	bool read() {
		int x, y;
		scanf("%d%d", &x, &y);
		this->x = x;
		this->y = y;
		return x >= 0 || y >= 0;
	}
	
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	
	friend Point operator * (const Point &a, const long double &k) {
		return Point(a.x * k, a.y * k);
	}

	friend Point operator / (const Point &a, const long double &k) {
		return Point(a.x / k, a.y / k);
	}
};

const Point dir[] = {Point(0, 1), Point(0, -1), Point(1, 0), Point(-1, 0)};

Point a, b, c;

__inline long double sqr(const long double &x) {
	return x * x;
}

__inline long double dist(const Point &a, const Point &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

__inline long double dist(int type, const Point &p) {
	long double dista = dist(p, a);
	long double distb = dist(p, b);
	long double distc = dist(p, c);
	if (type == 0) {
		return dista + distb * 2 + distc * 2;
	}
	if (type == 1) {
		return dista * 2 + distb + distc * 2;
	}
	if (type == 2) {
		return dista * 2 + distb * 2 + distc;
	}
	assert(false);
}

long double random_walk(int type, const long double &init, Point a) {
	for (long double step = 4000.; step >= eps; step *= .5) {
		bool flag = true;
		while (flag) {
			flag = false;
			
			for (int i = 0; i < 4; ++i) {
				Point b = a + dir[i] * step;
				if (dist(type, b) < dist(type, a)) {
					flag = true;
					a = b;
					break;
				}
			}
		}
	}
	return dist(type, a);
}

void solve(void) {
	long double xmin = min(min(a.x, b.x), c.x);
	long double xmax = max(max(a.x, b.x), c.x);
	long double ymin = min(min(a.y, b.y), c.y);
	long double ymax = max(max(a.y, b.y), c.y);
	
	long double range = max(xmax - xmin, ymax - ymin);
	
	long double ret = random_walk(0, range, (a + b + c) / 3);
	ret = min(ret, random_walk(1, range, (a + b + c) / 3));
	ret = min(ret, random_walk(2, range, (a + b + c) / 3));
	
	printf("%.8f\n", (double)ret);
}

int main(void) {
	for (int tests = 1; ; ++tests) {
		bool flag = a.read();
		flag |= b.read();
		flag |= c.read();
		if (!flag) {
			break;
		}
		printf("Case %d: ", tests);
		solve();
	}
}
