#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

const int N = 200;

int n, m, perm[N][N];
int element[N], temp[N];

bool check(int element[]) {
	for (int turns = 1; turns <= m; ++turns) {
		sort(element + 1, element + n / 2 + 1);
		sort(element + n / 2 + 1, element + n + 1);
		if (turns < m) {
			for (int i = 1; i <= n; i++) {
				temp[i] = element[perm[turns][i]];
			}
			for (int i = 1; i <= n; i++) {
				element[i] = temp[i];
			}
		}
	}
	for (int i = 1; i < n; i++) {
		if (element[i] > element[i + 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = m - 1; i >= 1; i--) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &perm[i][j]);
		}
	}

	for (int len1 = 0; len1 <= n / 2; ++len1) {
		for (int len2 = 0; len2 <= n / 2; ++len2) {
			for (int i = 1; i <= n; ++i) {
				element[i] = 1;
			}
			for (int i = 1; i <= len1; ++i) {
				element[i] = 0;
			}
			for (int i = n / 2 + 1; i <= n / 2 + len2; ++i) {
				element[i] = 0;
			}
			if (!check(element)) {
				puts("No");
				return 0;
			}
		}
	}
	
	puts("Yes");
	return 0;
}
