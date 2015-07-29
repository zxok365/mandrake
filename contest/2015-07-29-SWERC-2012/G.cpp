#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

const int N = 222222;

int d, p;
int element[N], a[N];

void solve(void) {
	string buffer;
	getline(cin, buffer);
	
	int n = 0;
	for (stringstream os(buffer); os >> element[n++]; );
	n--;
	
	if (n == d + 1) {
		for (int i = 0; i <= d; ++i) {
			a[i] = element[i];
		}
	} else if (element[1] == 0) {
		puts("The spider may fall!");
		return;
	} else {
		int numerator = element[3] * element[0] - element[1] * element[2];
		int denominator = element[2] * element[0] - element[1] * element[1];
		double coe1 = (denominator == 0) ? element[2] / element[1] : numerator / denominator;
		double coe2 = (element[3] - element[2] * coe1) / element[1];
		
		for (int i = 0; i < 4; ++i) {
			a[i] = element[i];
		}
		for (int i = 4; i <= d; ++i) {
			a[i] = coe1 * a[i - 1] + coe2 * a[i - 2];
		}
	}
	
	if (a[0] > p) {
		puts("The spider is going to fall!");
		return;
	}
	for (int i = 0; i <= d; ++i) {
		if (a[i] > p) {
			printf("%d\n", d - i + 1);
			return;
		}
	}
	puts("The spider may fall!");
}

int main(void) {
	ios::sync_with_stdio(false);
	for (; cin >> d >> p; solve());
}
