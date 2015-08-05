#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 1111;

int n, m;
double prob[N];

int main(void) {
	scanf("%d%d", &n, &m);
	prob[n] = 1.;
	for (int i = n; i >= 1; --i) {
		for (int j = 1; j <= min(i, m); ++j) {
			prob[i - j] += prob[i] / i;
		}
	}
	printf("%.10f\n", prob[0]);
}
