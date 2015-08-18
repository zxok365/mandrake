#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;
const double pi = acos(-1.);
const double eps = 1e-8;

int main() {
	double h, lambda;
	scanf("%lf%lf", &h, &lambda);
	double r = 1.;
	double l = sqrt(r * r - h * h) / r;
	
	double alpha = asin(l / r);
	double theta = asin(1. / lambda);
	
	double angle = alpha + theta;
	
	if (pi - angle * 2 < eps) {
		puts("1.0000000000");
		return 0;
	}
	
	double len = 2 * r * cos(angle);
	
	double height = h + r - len * cos(theta);

	double area = 2 * pi * height * r;
	double tot_area = 4 * pi * r - 2 * pi * r * (r - h);
	
	double ans = area / tot_area;
	
	printf("%.10f\n", ans);
	
	return 0;
}
