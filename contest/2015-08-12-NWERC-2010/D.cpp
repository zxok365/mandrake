#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>


using namespace std;
const double eps = 1e-8;
const int N = 111111;
int n;
double cost_flat, cost_hill, vmax, rest;

double  y[N], x[N];
long double  dist[N];

bool check(double v) {
	double cost = 0;
	for (int i = 1; i <= n; i++) {
		double s = y[i] / x[i];
		if (y[i] >= 0) {
			cost += dist[i] * cost_flat * v + dist[i] * cost_hill * s;
		}
		else {
			double tmp = dist[i] * cost_flat * v + cost_hill * s * dist[i];
			if (tmp > 0) cost += tmp;
		}
	}
	return cost <= rest;
}

double getans(double v) {
	double ret = 0;
	for (int i = 1; i <= n; i++) {
		double s = y[i] / x[i];
		if (y[i] >= 0) {
			ret += dist[i] / v;
		}
		else {
			double vv = -cost_hill * s / cost_flat;
			double nowv = min(vmax, max(v, vv));
			ret += dist[i] / nowv;
		}
	}
	return ret;
}
double getdist(double x, double y) {
	return sqrt(x * x + y * y);
}
void solve() {
	scanf("%lf%lf%lf%lf", &cost_flat, &cost_hill, &vmax, &rest);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &x[i], &y[i]);
		x[i] /= 1000; y[i] /= 1000;
	}
	
	for (int i = 1; i <= n; i++) {
		dist[i] = getdist(x[i], y[i]);
	}
	
	double l = 0, r = vmax;
	while (l < r - 1e-11) {
		double mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		}
		else r = mid;
	}
	
	if (check(l)) {
		printf("%0.8f\n", getans(l));
	}
	else {
		puts("IMPOSSIBLE");
	}
}

int main() {
	int test;
	scanf("%d", &test);
	for (int i = 1; i <= test; i++) {
		solve();
	}
	return 0;
}
