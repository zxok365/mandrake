#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>

const double eps = 1e-8;
const double PI = acos(-1.);

__inline double sqr(const double &x) {
	return x * x;
}

__inline double fix(const double &x) {
	if (x < -PI) {
		return x + PI * 2;
	}
	if (x > PI) {
		return x - PI * 2;	
	}
	return x;
}

__inline double get(double x) {
	if (x < 0) {
		x += 2.0 * PI;
	}
	return x;
}

__inline double calc(const double &radius1, const double &radius2, const double &angle) {
	return angle * (radius2 / radius1) + angle;
}

__inline double compute(const double &lena, const double &lenb, const double &lenc) {
	return acos((sqr(lena) + sqr(lenb) - sqr(lenc)) / (lena * lenb * 2));
}

class Point {
public:
	double x, y;
	
	Point() {}
	
	Point(const double &x, const double &y) : x(x), y(y) {}
	
	void read() {
		scanf("%lf%lf", &x, &y);
	}
};

__inline double dist(const Point &a, const Point &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

__inline double atan2(const Point &a, const Point &b) {
	return atan2(b.y - a.y, b.x - a.x);
}

class Circle {
public:
	Point center;
	double radius;
	
	void read() {
		center.read();
		scanf("%lf", &radius);
	}
};

const int N = 2222;

int n;
Circle a[N], coin;

void solve(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		a[i].read();
	}
	coin.read();
	
	std::pair<int, double> current = std::make_pair(0, 0);
	for (int i = 0; i < n; ++i) {
		double total = a[i].radius + coin.radius;
		if (std::abs(dist(coin.center, a[i].center) - total) < eps) {
			current = std::make_pair(i, atan2(a[i].center, coin.center));
			break;
		}
	}

	double answer = 0;
	std::pair<int, double> pos = current;
	for (int counter = 1; ; counter++) {
		std::pair<double, int> best = std::make_pair(PI * 2, -1);
		for (int i = 0; i < n; ++i) {
			if (i == pos.first) {
				continue;
			}
			double total = a[pos.first].radius + a[i].radius + coin.radius * 2;
			if (dist(a[pos.first].center, a[i].center) < total + eps) {
				double alpha = compute(dist(a[pos.first].center, a[i].center),
											a[pos.first].radius + coin.radius,
											a[i].radius + coin.radius);
				double angle = fix(alpha + atan2(a[pos.first].center, a[i].center));
				best = std::min(best, std::make_pair(get(pos.second - angle), i));
			}
		}
		
		if (best.second == -1) {
			answer = calc(coin.radius, a[pos.first].radius, PI * 2);
			break;
		}
		
		if (pos.first == current.first) {
			double left = pos.second - best.first;
			double right = pos.second;
			for (; left > right; right += PI * 2);
			double number = current.second;
			for (; number > right - eps; number -= PI * 2);
			for (; number < left; number += PI * 2);
			if (left - eps < number && number < right + eps && counter > 1) {
				if (pos.second < current.second) {
					pos.second += PI * 2;
				}
				answer += calc(coin.radius, a[pos.first].radius, pos.second - current.second);
				break;
			}
		}
		answer += calc(coin.radius, a[pos.first].radius, best.first);
		pos = std::make_pair(best.second, fix(atan2(a[best.second].center, a[pos.first].center) - compute(dist(a[pos.first].center, a[best.second].center),
																											a[best.second].radius + coin.radius,
																											a[pos.first].radius + coin.radius))
							);
	}
	
	printf("%.10f\n", answer / PI * 180.);
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
