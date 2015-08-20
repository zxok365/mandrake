#include <cstdio>
#include <cstring>
#include <complex>
#include <cmath>
#include <algorithm>
#include <vector>

typedef std::complex<double> Complex;

const double PI = acos(-1.);

const unsigned long long MAGIC = 4423;
const int N = 555555;

int n, m, k;
char text[N];
int a[N], b[N], answer[N];
Complex number1[N], number2[N], number[N];
unsigned long long magic[N], hash[N];

__inline int lowbit(int x) {
	return x & -x;
}

void solve(Complex number[], int length, int type) {
	for (int i = 1, j = 0; i < length - 1; ++i) {
		for (int k = length; j ^= k >>= 1, ~j & k; );
		if (i < j) {
			std::swap(number[i], number[j]);
		}
	}
	Complex unit_p0;
	for (int turn = 0; (1 << turn) < length; ++turn) {
		int step = 1 << turn, step2 = step << 1;
		double p0 = PI / step * type;
		sincos(p0, &unit_p0.imag(), &unit_p0.real());
		for (int i = 0; i < length; i += step2) {
			Complex unit = 1;
			for (int j = 0; j < step; ++j) {
				Complex &number1 = number[i + j + step];
				Complex &number2 = number[i + j];
				Complex delta = unit * number1;
				number1 = number2 - delta;
				number2 = number2 + delta;
				unit = unit * unit_p0;
			}
		}
	}
}

void calc() {
	int length = n + m;
	for (; lowbit(length) != length; ++length);

	std::fill(number1, number1 + length, 0);
	std::fill(number2, number2 + length, 0);
	for (int i = 0; i < n; ++i) {
		number1[m + i] = a[i];
	}
	for (int i = 0; i < m; ++i) {
		number2[i] = b[i];
	}

	solve(number1, length, 1);
	solve(number2, length, 1);
	for (int i = 0; i < length; ++i) {
		number[i] = number1[i] * number2[i];
	}
	solve(number, length, -1);
	for (int i = 0; i < length; ++i) {
		answer[i] += (int)(number[i].real() / length + 0.5);
	}
}

void solve(void) {
	scanf("%s", text);
	n = (int)strlen(text);
	for (int i = 0; i < n; ++i) {
		a[i] = text[i] - 'a';
	}
	scanf("%s", text);
	m = (int)strlen(text);
	for (int i = 0; i < m; ++i) {
		b[i] = text[i] - 'a';
	}
	if (n < m) {
		puts("0");
		return;
	}

	magic[0] = 1, hash[0] = 0;
	for (int i = 1; i <= n; ++i) {
		magic[i] = magic[i - 1] * MAGIC;
		hash[i] = hash[i - 1] * MAGIC + a[i - 1];
	}

	std::fill(answer, answer + n + m, 0);
	std::reverse(b, b + m);
	
	calc();
	for (int i = 0; i < n; ++i) {
		a[i] ^= 1;
	}
	for (int i = 0; i < m; ++i) {
		b[i] ^= 1;
	}
	calc();
	
	std::vector<unsigned long long> value;
	for (int i = 0; i + m - 1 < n; ++i) {
		if (m - answer[m + m - 1 + i] <= k) {
			value.push_back(hash[i + m] - hash[i] * magic[m]);
		}
	}
	std::sort(value.begin(), value.end());
	value.erase(std::unique(value.begin(), value.end()), value.end());
	printf("%d\n", (int)value.size());
}

int main(void) {
	for (int tests = 1; scanf("%d", &k) && ~k; ++tests) {
		printf("Case %d: ", tests);
		solve();
	}
}

