#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
const int N = 111111;
int n;
int a[N], b[N];
pair<int, int> ans[N];
void recover() {
	for (int i = 0; i < n; i++) {
		a[i] = b[i];
	}
}
int check() {
	for (int i = 0; i < n; i++) {
		if (a[i] != a[(i + 1) % n]) return 0;
	}
	return 1;
}
void solve() {
	scanf("%d", &n);
	long long sum = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		sum += a[i];
	}
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}

	if (sum % n != 0) {
		puts("NO");
		return;
	}
	long long average = sum / n;
	int tot = 1;
	
	if (check()) {
		puts("YES");
		puts("0");
		return;
	}
	
	if (a[n - 1] > 0) {
		a[0]++;
		a[n - 1]--;
		tot = 1;
		ans[1] = make_pair(n - 1, 0);
		for (int i = 0; i < n - 1; i++) {
			if (a[i] < average) {
				a[i]++;
				a[i + 1]--;
				ans[++tot] = make_pair(i  + 1, i);
			} else {
				if (a[i] > average) {
					a[i]--;
					a[i + 1]++;
					ans[++tot] = make_pair(i, i + 1);
				}
			}
		}
		if (check()) {
			puts("YES");
			printf("%d\n", tot);
			for (int i = 1; i <= tot; i++) {
				printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
			}
			return;
		}
	}
	recover();
	
	if (a[0] > 0) {
		a[0]--;
		a[n - 1]++;
		tot = 1;
		ans[1] = make_pair(0, n - 1);
		for (int i = 0; i < n - 1; i++) {
			if (a[i] < average) {
				a[i]++;
				a[i + 1]--;
				ans[++tot] = make_pair(i + 1, i);
			} else {
				if (a[i] > average) {
					a[i]--;
					a[i + 1]++;
					ans[++tot] = make_pair(i , i + 1);
				}
			}
		}
		if (check()) {
			puts("YES");
			printf("%d\n", tot);
			for (int i = 1; i <= tot; i++) {
				printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
			}
			return;
		}
	}
	recover();
	tot = 0;
	for (int i = 0; i < n - 1; i++) {
			if (a[i] < average) {
				a[i]++;
				a[i + 1]--;
				ans[++tot] = make_pair(i + 1, i);
			} else {
				if (a[i] > average) {
					a[i]--;
					a[i + 1]++;
					ans[++tot] = make_pair(i, i + 1);
				}
			}
		}
	
	if (check()) {
			puts("YES");
			printf("%d\n", tot);
			for (int i = 1; i <= tot; i++) {
				printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
			}
			return;
	}
	
	puts("NO");
}
int main() {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; i++) {
		solve();
	}
	return 0;
}

