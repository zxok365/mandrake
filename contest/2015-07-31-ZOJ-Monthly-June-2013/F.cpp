#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 111111;

int n, comps;
vector<int> comp[N];
pair<pair<int, int>, int> a[N];

void solve(void) {
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &a[i].first.first, &a[i].first.second);
		a[i].second = i + 1;
	}
	
	comps = 0;
	for (int i = 0; i < n; ++i) {
		comp[i].clear();
	}
	
	sort(a, a + n);
	for (int i = 0; i < n; ++i) {
		if (i == 0 || a[i].first.first >= a[i - 1].first.second) {
			comp[comps++].push_back(a[i].second);
		} else {
			a[i].first.second = min(a[i].first.second, a[i - 1].first.second);
			comp[comps - 1].push_back(a[i].second);
		}
	}
	
	printf("%d\n", comps);
	for (int i = 0; i < comps; ++i) {
		for (int j = 0; j < (int)comp[i].size(); ++j) {
			printf("%d%s", comp[i][j], (j == (int)comp[i].size() - 1) ? "\n" : " ");
		}
	}
	puts("");
}

int main(void) {
	for (; ~scanf("%d", &n); solve());
}
