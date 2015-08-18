#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

const double PI = acos(-1.);
const double eps = 1e-11;

__inline int sgn(const double &x) {
	return x < -eps ? -1 : x > eps;
}

__inline double sqr(const double &x) {
	return x * x;
}

class Point {
public:
	double x, y;
	int i;
	
	Point(const double &x, const double &y, int i) : x(x), y(y), i(i) {}
	
	friend bool operator < (const Point &a, const Point &b) {
		if (sgn(a.x - b.x) != 0) {
			return sgn(a.x - b.x) < 0;
		} else {
			return sgn(a.y - b.y) < 0;
		}
	}
	
	friend double det(const Point &a, const Point &b, const Point &c) {
		return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	}
};

class Circle {
public:
	double x, y, r;
	
	Point getPoint(const double &angle, int i) {
		return Point(x + r * cos(angle), y + r * sin(angle), i);
	}
};

std::vector<Point> convex_hull(std::vector<Point> point) {
	std::sort(point.begin(), point.end());
	std::vector<Point> convex;
	{
		std::vector<Point> stack;
		for (int i = 0; i < (int)point.size(); ++i) {
			while ((int)stack.size() >= 2 && sgn(det(stack[(int)stack.size() - 2], stack.back(), point[i])) <= 0) {
				stack.pop_back();
			}
			stack.push_back(point[i]);
		}
		for (int i = 0; i < (int)stack.size(); ++i) {
			convex.push_back(stack[i]);
		}
	}
	{
		std::vector<Point> stack;
		for (int i = (int)point.size() - 1; i >= 0; --i) {
			while ((int)stack.size() >= 2 && sgn(det(stack[(int)stack.size() - 2], stack.back(), point[i])) <= 0) {
				stack.pop_back();
			}
			stack.push_back(point[i]);
		}
		for (int i = 1; i < (int)stack.size() - 1; ++i) {
			convex.push_back(stack[i]);
		}
	}
	return convex;
}

const int N = 1111;

int n;
Circle a[N];

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%lf%lf%lf", &a[i].x, &a[i].y, &a[i].r);
	}
	
	double answer = 0;
	if (n == 1) {
		answer = 2 * PI * a[0].r;
	} else {
		std::vector<Point> point;
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				double d2 = sqr(a[i].x - a[j].x) + sqr(a[i].y - a[j].y);
				double base = atan2(a[j].y - a[i].y, a[j].x - a[i].x);
				double angle = acos((a[i].r - a[j].r) / sqrt(d2));
				point.push_back(a[i].getPoint(base + angle, i));
				point.push_back(a[j].getPoint(base + angle, j));
				point.push_back(a[i].getPoint(base - angle, i));
				point.push_back(a[j].getPoint(base - angle, j));
			}
		}
		
		std::vector<Point> convex = convex_hull(point);
		for (int i = 0; i < (int)convex.size(); ++i) {
			int j = (i + 1) % (int)convex.size();
			if (convex[i].i == convex[j].i) {
				Circle circle = a[convex[i].i];
				double angle = atan2(convex[j].y - circle.y, convex[j].x - circle.x)
							 - atan2(convex[i].y - circle.y, convex[i].x - circle.x);
				if (sgn(angle) < 0) {
					angle += 2 * PI;
				}
				answer += circle.r * angle;
			} else {
				answer += sqrt(sqr(convex[j].x - convex[i].x) + sqr(convex[j].y - convex[i].y));
			}
		}
	}
	printf("%.10f\n", answer);
}
