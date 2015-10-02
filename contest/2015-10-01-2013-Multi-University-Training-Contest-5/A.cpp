#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

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

const int N = 111;

int n, m, q;
Point city[N], base[N];

int pivot;
__inline bool compare(const std::pair<Point, std::pair<int, int> > &a, const std::pair<Point, std::pair<int, int> > &b) {
	return dist(city[pivot], a.first) < dist(city[pivot], b.first);
}

__inline int near(const Point &a) {
	int j = 0;
	for (int i = 0; i < m; ++i) {
		if (dist(a, base[i]) < dist(a, base[j])) {
			j = i;
		}
	}
	return j;
}

void solve(void) {
	for (int i = 0; i < n; ++i) {
		city[i].read();
	}
	for (int i = 0; i < m; ++i) {
		base[i].read();
	}
	for (scanf("%d", &q); q--; ) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		
		std::vector<std::pair<Point, std::pair<int, int> > > list;
		for (int i = 0; i < m; ++i) {
			for (int j = i + 1; j < m; ++j) {
				Point mid = (base[i] + base[j]) / 2;
				Point dir = base[j] - base[i];
				Point per = Point(-dir.y, dir.x);
				Point c = mid - per, d = mid + per;
				if (!check(city[a], city[b], c, d)) {
					continue;
				}
				Point in = intersect(city[a], city[b], c, d);
				if (!point_on_line(in, city[a], city[b])) {
					continue;
				}
				list.push_back(std::make_pair(in, std::make_pair(i, j)));
			}
		}
		
		pivot = a;
		std::sort(list.begin(), list.end(), compare);
		
		int answer = 0;
		
		int pos = near(city[a]);
		for (int k = 0; k < (int)list.size(); ++k) {
			int i = list[k].second.first, j = list[k].second.second;
			
			for (double step = eps; ; step *= 2) {
				Point c = list[k].first - (city[b] - city[a]).norm() * step;
				if (std::abs(dist(c, base[i]) - dist(c, base[j])) < eps) {
					continue;
				}
				if (dist(c, base[i]) > dist(c, base[j])) {
					std::swap(i, j);
				}
				break;
			}
			
			if (i == pos) {
				pos = j;
				answer++;
			}
		}
		
		printf("%d\n", answer);
	}
}

int main(void) {
	for (; ~scanf("%d%d", &n, &m); solve());
}
