#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

__inline int sgn(const double &x, const double &eps = 1e-8) {
	return (x < -eps) ? -1 : (x > eps);
}

class Point {
public:
	double x, y;

	Point() {}

	Point(const double &x, const double &y) : x(x), y(y) {}
	
	void read() {
		scanf("%lf%lf", &x, &y);
	}
	
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}

	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}

	friend Point operator * (const Point &a, const double &k) {
		return Point(a.x * k, a.y * k);
	}

	friend Point operator * (const double &k, const Point &a) {
		return Point(a.x * k, a.y * k);
	}

	friend Point operator / (const Point &a, const double &k) {
		return Point(a.x / k, a.y / k);
	}

	friend bool operator == (const Point &a, const Point &b) {
		return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
	}

	friend bool operator < (const Point &a, const Point &b) {
		if (sgn(a.x - b.x) == 0) {
			return sgn(a.y - b.y) < 0;
		} else {
			return sgn(a.x - b.x) < 0;
		}
	}

	friend double det(const Point &a, const Point &b) {
		return a.x * b.y - a.y * b.x;
	}

	friend double det(const Point &a, const Point &b, const Point &c) {
		return det(b - a, c - a);
	}

	friend double dot(const Point &a, const Point &b) {
		return a.x * b.x + a.y * b.y;
	}
	
	friend double dot(const Point &a, const Point &b, const Point &c) {
		return dot(b - a, c - a);
	}

	friend bool proper_intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
		double s1 = det(a, b, c);
		double s2 = det(a, b, d);
		if (sgn(s1 - s2) == 0) {
			return false;
		}
		double c1 = det(a, b, c);
		double c2 = det(a, b, d);
		double c3 = det(c, d, a);
		double c4 = det(c, d, b);
		return sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0;
	}
	
	friend Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
		double s1 = det(a, b, c);
		double s2 = det(a, b, d);
		return (s1 * d - s2 * c) / (s1 - s2);
	}
};

const int N = 1111;

int n;
Point a[N];

void solve(void) {
	for (int i = 0; i < n; ++i) {
		a[i].read();
	}
	
	vector<Point> vertex;
	for (int i = 0; i < n; ++i) {
		vertex.push_back(a[i]);
	}
	
	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n - 1; ++j) {
			if (proper_intersect(a[i], a[i + 1], a[j], a[j + 1])) {
				vertex.push_back(intersect(a[i], a[i + 1], a[j], a[j + 1]));
			}
		}
	}
	
	sort(vertex.begin(), vertex.end());
	vertex.erase(unique(vertex.begin(), vertex.end()), vertex.end());
	
	int edge = n - 1;
	for (int i = 0; i < (int)vertex.size(); ++i) {
		for (int j = 0; j < n - 1; ++j) {
			if (sgn(det(vertex[i], a[j], a[j + 1])) == 0 && sgn(dot(vertex[i], a[j], a[j + 1])) < 0) {
				edge++;
			}
		}
	}
	
	printf("There are %d pieces.\n", edge - (int)vertex.size() + 2);
}

int main(void) {
	for (int tests = 1; scanf("%d", &n) && n; ++tests) {
		printf("Case %d: ", tests);
		solve();
	}
}

