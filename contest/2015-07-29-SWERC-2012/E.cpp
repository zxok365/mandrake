#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <iostream>
#include <cstring>

using namespace std;

const long long MOD = 1e6 + 3;

const int N = 777;

class Point {
public:
	long long x, y;
	
	Point() {}
	
	Point(const long long &x, const long long &y) : x(x), y(y) {}
	
	void operator += (const Point &other) {
		(x += other.x) %= MOD;
		(y += other.y) %= MOD;
	}

	void operator -= (const Point &other) {
		(x -= other.x) %= MOD;
		(y -= other.y) %= MOD;
	}
	
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y);
	}
	
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	
	friend long long det(const Point &a, const Point &b) {
		return a.x * b.y - a.y * b.x;
	}
};

__inline long long comb2(const long long &x) {
	return (x * (x - 1) >> 1) % MOD;
}

int n;
Point point[N];
long long counter[N][N];

void solve(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%lld%lld", &point[i].x, &point[i].y);
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			counter[i][j] = 0;
		}
	}
	
	long long result = 0;
	for (int pivot = 0; pivot < n; ++pivot) {
		static pair<double, int> value[N << 1];
		
		int size = 0;
		for (int i = 0; i < n; ++i) {
			if (i == pivot) {
				continue;
			}
			Point vec = point[i] - point[pivot];
			value[size++] = make_pair(atan2(vec.y, vec.x), i);
		}

		sort(value, value + size);
		for (int i = 0; i < size; ++i) {
			value[i + size] = value[i];
		}

		long long area = 0;
		Point total = Point(0, 0);
		for (int i = 0, j = 0; i < size; ++i) {
			for (; j - i < size && det(point[value[i].second] - point[pivot], point[value[j].second] - point[pivot]) >= 0; ++j) {
				area += det(total, point[value[j].second] - point[pivot]);
				area += det(point[value[j].second], point[pivot]) * (j - i);
				area %= MOD;
				total += point[value[j].second];
			}
			
			counter[pivot][value[i].second] = j - i - 1;
			
			total -= point[value[i].second];
			area -= det(point[value[i].second] - point[pivot], total);
			area -= det(point[pivot], point[value[i].second]) * (j - i - 1);
			area %= MOD;

			(result -= area) %= MOD;
		}	
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			result += det(point[i], point[j]) * comb2(counter[i][j]);
			result += det(point[i], point[j]) * counter[i][j] * (n - 3);
			result %= MOD;
		}
	}
	
	printf("%d\n", (int)((result + MOD) % MOD));
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case %d: ", i);
		solve();
	}
}
