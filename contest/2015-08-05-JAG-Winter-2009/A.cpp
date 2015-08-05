#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

const double eps = 1e-6;

int n;
double a[3][3], b[3], element[3][3];

double det() {
/*	for (int i = 0; i < 3; ++i, puts("")) {
		for (int j = 0; j < 3; ++j, putchar(' ')) {
			printf("%.3f", element[i][j]);
		}
	}
*/	double result = 1;
	for (int i = 0; i < 3; ++i) {
		int index = i;
		for (int j = i; j < 3; ++j) {
			if (fabs(element[j][i]) > fabs(element[index][i])) {
				index = j;
			}
		}
		if (index != i) {
			for (int j = 0; j < 3; ++j) {
				swap(element[index][j], element[i][j]);
			}
			result = -result;
		}
		for (int j = i + 1; j < 3; ++j) {
			double coe = element[j][i] / element[i][i];
			for (int k = 0; k < 3; ++k) {
				element[j][k] -= coe * element[i][k];
			}
		}
	}
	for (int i = 0; i < 3; ++i) {
		result *= element[i][i];
	}
//	printf("%.10f\n", result);
	return result;
}

int main() {
	scanf("%d", &n);
	for(int i = 0; i < n; i++) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		a[0][0] += x * x;
		a[0][1] += x * y;
		a[0][2] += x;
		a[1][0] += x * y;
		a[1][1] += y * y;
		a[1][2] += y;
		a[2][0] += x;
		a[2][1] += y;
		a[2][2] += 1;
		b[0] += (x * x + y * y) * x;
		b[1] += (x * x + y * y) * y;
		b[2] += x * x + y * y;
	}
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			element[i][j] = a[i][j];
		}
	}
	double base = det();
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			element[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < 3; ++i) {
		element[i][0] = b[i];
	}
	
	double result1 = -det() / base;
	
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			element[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < 3; ++i) {
		element[i][1] = b[i];
	}
	
	double result2 = -det() / base;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			element[i][j] = a[i][j];
		}
	}
	for (int i = 0; i < 3; ++i) {
		element[i][2] = b[i];
	}
	
	double result3 = -det() / base;
	
	if (fabs(result1) < eps) {
		result1 = 0;
	}
	if (fabs(result2) < eps) {
		result2 = 0;
	}
	if (fabs(result3) < eps) {
		result3 = 0;
	}
	
	printf("%.3f %.3f %.3f\n", result1, result2, result3);
	return 0;
}
