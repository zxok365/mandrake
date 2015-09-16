#include <cstdio>
#include <string>

const int N = 1111;

int n, m;
int a[N];
std::string route[N];

void dfs(int left, int right, const std::string &text) {
	if (left > right) {
		return;
	}
	int pivot = a[left];
	route[pivot] = text;
	
	for (int i = left + 1; i <= right; ++i) {
		if (a[i] > pivot) {
			dfs(left + 1, i - 1, text + 'E');
			dfs(i, right, text + 'W');
			return;
		}
	}
	dfs(left + 1, right, text + 'E');
}

void solve(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
	}
	dfs(1, n, "");
	for (scanf("%d", &m); m--; ) {
		int x;
		scanf("%d", &x);
		printf("%s\n", route[x].c_str());
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
