#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

__inline int sgn(const double &x, const double &eps = 1e-8) {
	return (x < -eps) ? -1 : (x > eps);
}

class Point {
public:
	double x, y;

	Point() {}

	Point(const double &x, const double &y) : x(x), y(y) {}

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

	friend double det(const Point &a, const Point &b) {
		return a.x * b.y - a.y * b.x;
	}

	friend double det(const Point &a, const Point &b, const Point &c) {
		return det(b - a, c - a);
	}

	friend double dot(const Point &a, const Point &b) {
		return a.x * b.x + a.y * b.y;
	}

	friend Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
		double s1 = det(a, b, c);
		double s2 = det(a, b, d);
		return (s1 * d - s2 * c) / (s1 - s2);
	}
};
bool point_on_line(const Point &a, const Point &b, const Point &c) {
	return sgn(det(a - b, c - b)) == 0 && sgn(dot(b - a, c - a)) <= 0;
}

bool point_in_polygon(const Point &p, const vector<Point> &polygon) {
	int counter = 0;
	for (int i = 0; i < (int)polygon.size(); ++i) {
		Point a = polygon[i], b = polygon[(i + 1) % (int)polygon.size()];
		if (point_on_line(p, a, b)) {
			return true;
		}
		int x = sgn(det(p - a, b - a));
		int y = sgn(a.y - p.y);
		int z = sgn(b.y - p.y);
		counter += (x > 0 && y <= 0 && z > 0);
		counter -= (x < 0 && z <= 0 && y > 0);
	}
	return counter;
}

int n;
Point high, low;
double a, b;

void solve(void) {
	vector<Point> poly;
	scanf("%d%lf%lf", &n, &a, &b);
	for (int i = 0; i < n; ++i) {
		Point p;
		scanf("%lf%lf", &p.x, &p.y);
		poly.push_back(p);
	}
	
	double counter = 0;
	for (int x = (int)ceil(low.x); x <= (int)floor(high.x); ++x) {
		for (int y = (int)ceil(low.y); y <= (int)floor(high.y); ++y) {
			if (point_in_polygon(Point(x, y), poly)) {
				double x1 = max(low.x, x - 0.5);
				double y1 = max(low.y, y - 0.5);
				double x2 = min(high.x, x + 0.5);
				double y2 = min(high.y, y + 0.5);
				
				counter += (a * x + b * y) * (x2 - x1) * (y2 - y1);
			}
		}
	}
	
	double result = counter / (high.x - low.x) / (high.y - low.y);
	
	printf("%.3f\n", result);
}

int main(void) {
	for (; ~scanf("%lf%lf%lf%lf", &low.x, &low.y, &high.x, &high.y); solve());
}
