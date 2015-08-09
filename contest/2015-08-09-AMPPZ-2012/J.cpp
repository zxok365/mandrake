#include <cstdio>
#include <algorithm>
#include <climits>

const int N = 1111111;

int n;
std::pair<int, int> a[N];

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].second, &a[i].first);
	}
	std::sort(a, a + n);
	int answer = INT_MAX, total = 0;
	for (int i = 0; i < n; ++i) {
		total += a[i].second;
		answer = std::min(answer, a[i].first - total);
	}
	printf("%d\n", answer);
}
