#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
int w, h, pos, x, y;
double lambda;
bool check(double t) {
	double len = (h - t) / (1. * (y - h)) * (x - w);
	double Sina = (x - w) / sqrt(1. * (y - h) * (y - h) + 1. * (x - w) * (x - w));
	double Sinb = Sina / lambda;
	double Tanb = (Sinb) / sqrt(1 - Sinb * Sinb);
	double npos = w - len - Tanb * t;
	if (npos >= pos) return true;
	return false;
}

void solve() {
	scanf("%d%d%d%d%d%lf", &w, &h, &pos, &x, &y, &lambda);
	double le = 0, ri = h, mid;
	if (!check(ri)) {
		puts("Impossible");
		return;
	}
	for (int i = 0; i < 50; i++) {
		mid = (le + ri) / 2;
		if (check(mid)) ri = mid;
		else le = mid;
	}
	printf("%0.4f\n", le);
}
int main() {
	int test;
	scanf("%d", &test);
	for (int i = 1; i <= test; i++) {
		solve();
	}
	return 0;
}
