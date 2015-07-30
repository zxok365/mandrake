#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1111;
const int M = 22;

int n, m;
char a[N][M];
vector<pair<int, int> > value[2];

/*
	6.7.8
	.345.
	12!..
*/

bool put(int x, int y, int mask) {
//printf("%d %d %d\n", x, y, mask);
	//	1
	if (y > 1 && a[x][y - 1] == '.' && (mask >> 1 & 1)) {
		return false;
	}
	//	2
	if (y > 0 && (mask & 1)) {
		return false;
	}
	//	3
	if (x > 0 && y > 0 && (mask >> m & 1)) {
		return false;
	}
	//	4
	if (x > 0 && (mask >> m - 1 & 1)) {
		return false;
	}
	//	5
	if (x > 0 && y < m - 1 && (mask >> m - 2 & 1)) {
		return false;
	}
	//	6
	if (x > 1 && y > 1 && a[x - 1][y - 1] == '.' && (mask >> m + m + 1 & 1)) {
		return false;
	}
	//	7
	if (x > 1 && a[x - 1][y] == '.' && (mask >> m + m - 1 & 1)) {
		return false;
	}
	//	8
	if (x > 1 && y < m - 2 && a[x - 1][y + 1] == '.' && (mask >> m + m - 3 & 1)) {
		return false;
	}
	return true;
}

void solve() {
	int cover = (1 << m + m + 2) - 1;
	
	for (int i = 0; i < n; ++i) {
		scanf("%s", a[i]);
	}
	
	int now = 0;
	value[now].clear();
	value[now].push_back(make_pair(0, 0));
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			vector<pair<int, int> > &prev = value[now];
			value[now ^= 1].clear();
			
			//	unique
			sort(prev.begin(), prev.end());
			int size = 0;
			for (int k = 0; k < (int)prev.size(); ++k) {
				if (k == (int)prev.size() - 1 || prev[k].first != prev[k + 1].first) {
					prev[size++] = prev[k];
				}
			}
			prev.resize(size);
			
			for (int k = 0; k < (int)prev.size(); ++k) {
				value[now].push_back(make_pair((prev[k].first << 1) & cover, prev[k].second));
				if (a[i][j] == '.' && put(i, j, prev[k].first)) {
					value[now].push_back(make_pair((prev[k].first << 1 | 1) & cover, prev[k].second + 1));
				}
			}
		}
	}
	int result = 0;
	for (int i = 0; i < (int)value[now].size(); ++i) {
		result = max(result, value[now][i].second);
	}
	printf("%d\n", result);
}

int main(void) {
	for (; ~scanf("%d%d", &n, &m) && (n || m); solve());
}
