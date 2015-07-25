#include <cstdio>
#include <algorithm>

using namespace std;

const int N = 22222;

int n;
int son[N], bro[N];
pair<int, pair<int, int> > a[N];

int dfs(int x) {
	int sum = 0;
	for (int y = son[x]; ~y; y = bro[y]) {
		sum ^= dfs(y) + 1;
	}
	return sum;
}

__inline long long sqr(int x) {
	return 1LL * x * x;
}

__inline bool contain(const pair<int, pair<int, int> > &a, const pair<int, pair<int, int> > &b) {
	return sqr(a.second.first - b.second.first) + sqr(a.second.second - b.second.second) <= sqr(a.first - b.first);
}

void solve(void) {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &a[i].second.first, &a[i].second.second, &a[i].first);
	}
	
	for (int i = 0; i <= n; ++i) {
		son[i] = -1;
		bro[i] = -1;
	}
	
	sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; --i) {
		bool flag = false;
		for (int j = i + 1; j <= n; ++j) {
			if (contain(a[i], a[j])) {
				bro[i] = son[j];
				son[j] = i;
				flag = true;
				break;
			}
		}
		if (!flag) {
			bro[i] = son[0];
			son[0] = i;
		}
	}
	
	puts(dfs(0) ? "Alice" : "Bob");
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
