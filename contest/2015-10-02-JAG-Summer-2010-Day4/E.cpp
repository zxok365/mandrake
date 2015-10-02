#include <cstdio>
#include <algorithm>
#include <cmath>

const double PI = acos(-1.);
const double eps = 1e-8;

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
	
	double len() const {
		return sqrt(x * x + y * y);
	}
	
	Point norm() {
		return Point(x / len(), y / len());
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

	friend double dist(const Point &a, const Point &b) {
		return (a - b).len();
	}	
	
    friend bool check(const Point &a, const Point &b, const Point &c, const Point &d) {
        double s1 = det(a, b, c);
        double s2 = det(a, b, d);
        return sgn(s1 - s2) != 0;
    }
	
    friend Point intersect(const Point &a, const Point &b, const Point &c, const Point &d) {
        double s1 = det(a, b, c);
        double s2 = det(a, b, d);
        return (s1 * d - s2 * c) / (s1 - s2);
    }
};

bool point_on_line(const Point &p, const Point &a, const Point &b) {
    return sgn(det(p, a, b)) == 0 && sgn(dot(p, a, b)) <= 0;
}

const int N = 44444;

int n;
double amax;
Point a[N], b[N];
double pdist[N], radius[N], angle[N], vmax[N][2];

__inline double fix(double x) {
	for (; x < -eps; x += 2 * PI);
	for (; x > 2 * PI - eps; x -= 2 * PI);
	return x;
}

__inline std::pair<Point, Point> vertical(const Point &a, const Point &b) {
	Point vec = b - a;
	Point per = Point(-vec.y, vec.x);
	return std::make_pair(a, a + per);
}
int check(double mid, double v0, double v, double d) {
	double dist = v0 * mid + amax * mid * mid / 2;
	if (dist > d) return 0;
	if (v0 + mid * amax < v) return 1; 
	double need = (v0 + mid * amax - v) / amax;
	double nowv = v0 + mid * amax;
	if (nowv * need - .5 * need * need * amax + dist > d) return 0;
	return 1;
}

double get(double v0, double v, double d) {
	double l = 0, r = sqrt(2 * d / amax) + 100;
	int counter = 40;
	while (counter--) {
		double mid = (l + r) / 2;
		if (check(mid, v0, v, d)) l = mid;
		else r = mid;
	}
	
	double ret = (l + r) / 2;
	ret += (v0 + (l + r) / 2 * amax - v) / amax;
	return ret;
}

int main(void) {
	scanf("%d%lf", &n, &amax);
	for (int i = 0; i < n; ++i) {
		a[i].read();
		b[i].read();
		pdist[i] = dist(a[i], b[i]);
	}
	
	for (int i = 0; i < n - 1; ++i) {
		std::pair<Point, Point> pair1 = vertical(b[i], a[i]);
		std::pair<Point, Point> pair2 = vertical(a[i + 1], b[i + 1]);
		
		Point o;
		if (!check(pair1.first, pair1.second, pair2.first, pair2.second)) {
			o = (b[i] + a[i + 1]) / 2;
		} else {
			o = intersect(pair1.first, pair1.second, pair2.first, pair2.second);
		}
		radius[i] = dist(o, b[i]);
		
		double angle1 = atan2(b[i].y - o.y, b[i].x - o.x);
		double angle2 = atan2(a[i + 1].y - o.y, a[i + 1].x - o.x);
		
		if (sgn(det(b[i] - o, b[i] - a[i])) > 0) {
			angle[i] = fix(angle2 - angle1);
		} else {
			angle[i] = fix(angle1 - angle2);
		}
	}
	
	vmax[n - 1][0] = sqrt(2 * amax * pdist[n - 1]);
	vmax[n - 1][1] = 0;
	
	for (int i = n - 2; i >= 0; --i) {
		vmax[i][1] = std::min(sqrt(radius[i] * amax), vmax[i + 1][0]);
		vmax[i][0] = sqrt(vmax[i][1] * vmax[i][1] + 2 * amax * pdist[i]);
	}

	double nowv = 0;
	double ans = 0;
	
	for (int i = 0; i < n; i++) {
		if (nowv > vmax[i][1]) {
			double tmp = get(nowv, vmax[i][1], pdist[i]);
			ans += tmp;
			nowv = vmax[i][1];
		}
		else {	
			if (nowv * nowv + 2 * amax * pdist[i] < vmax[i][1] * vmax[i][1]) {
				double tmp = sqrt(nowv * nowv + 2 * amax * pdist[i]);
				ans += (tmp - nowv) / amax;
				nowv = tmp;
			} else {
				double tmp = get(nowv, vmax[i][1], pdist[i]);
	
				ans += tmp;
				nowv = vmax[i][1];
			}
		}
		if (i < n - 1) {
			ans += radius[i] * angle[i] / nowv;
		}		
	}
	
	printf("%0.9f\n", ans);
}
