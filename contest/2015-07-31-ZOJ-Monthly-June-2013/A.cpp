#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

pair<double, double> a[4];

__inline double sqr(const double &x) {
	return x * x;
}

__inline double dist(const pair<double, double> &a, const pair<double, double> &b) {
	return sqrt(sqr(a.first - b.first) + sqr(a.second - b.second));
}

void solve(void) {
	for (int i = 1; i < 4; ++i) {
		scanf("%lf%lf", &a[i].first, &a[i].second);
	}
	double result = dist(a[0], a[1]) + dist(a[2], a[3]);
	result = min(result, dist(a[0], a[2]) + dist(a[1], a[3]));
	result = min(result, dist(a[0], a[3]) + dist(a[1], a[2]));
	printf("%.10f\n", result);
}

int main(void) {
	for (; ~scanf("%lf%lf", &a[0].first, &a[0].second); solve());
}
