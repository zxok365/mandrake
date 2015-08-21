#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

const int MAX_S = 2222222;
using namespace std;
int cnt[11];
int tmp[11];
int dist[MAX_S + 10], q[MAX_S + 10];
int num[11], mypow[11], w[11], target;
int l, r;
int place(int tp, int pos, int state) {
	if (tp == 1) return 1;
	int up = pos - 3;
	int down = pos + 3;
	int left = pos - 1;
	int right = pos + 1;
	cnt[0] = cnt[1] = cnt[2] = cnt[3] = cnt[4] = 0;
	if (up >= 1) ++cnt[num[up]];
	if (down <= 9) ++cnt[num[down]];
	if (left % 3 > 0) ++cnt[num[left]];
	if (right % 3 != 1) ++cnt[num[right]];
	if (tp == 2) {
		return (cnt[1] > 0);
	}
	else {
		if (tp == 3) {
			return (cnt[1] && cnt[2]);
		}
		else {
			return (cnt[1] && cnt[2] && cnt[3]);
		}
	}
}

int calc(int state, int pos, int tp) {
	for (int i = 1; i <= 9; i++) {
		tmp[i] = state % 5;
		state /= 5;
	}
	tmp[pos] = tp;
	int ret = 0;
	for (int i = 1; i <= 9; i++) {
		ret += mypow[i - 1] * tmp[i];
	}
	return ret;
}

void bfs() {
	l = 0, r = 1;
	q[1] = 0;
	dist[0] = 1;
	while (l < r) {
		int state = q[++l];
		for (int i = 1; i <= 9; i++) {
			num[i] = state % 5;
			state /= 5;
		}
		
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 4; j++) {
				if (place(j, i, q[l])) {
					int newstate = calc(q[l], i, j);
					if (dist[newstate] == 0) {
						dist[newstate] = dist[q[l]] + 1;
						q[++r] = newstate;
					}
				}
			}
		}
	}
}

bool cmp(int x, int y) {
	return dist[x] < dist[y];
}


int start = 0;

void solve() {
	for (int now = 1; now <= r ; now++) {
		if (dist[q[now]] < 0) continue;
		int state = q[now];
		for (int i = 1; i <= 9; i++) {
			num[i] = state % 5;
			state /= 5;
		}
		int sum = 0;
		for (int i = 1; i <= 9; i++) {
			sum += w[num[i]];
		}
		if (sum >= target) {
			printf("%d\n", dist[q[now]] - 1);
			return;
		}
	}
	
	printf("Impossible\n");
}


int main() {
	mypow[0] = 1;
	for (int i = 1; i <= 9; i++) mypow[i] = mypow[i - 1] * 5;
	bfs();
	for (; scanf("%d%d%d%d%d", &w[1], &w[2], &w[3], &w[4], &target) == 5;) {
		static int test = 0;
		printf("Case %d: ", ++test);
		solve();
	}
	return 0;
}
