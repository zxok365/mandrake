#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 111111;
const int M = 1000000 + 11;
pair<pair<int, int>, int> event[N * 2];
int a[N], b[N], c[N], T[M], n;
int occur[M];
int lowbit(int x) {
	return x & -x;
}
void add(int x) {
	for (int i = x; i < M; i += lowbit(i)) T[i]++;
}

void dec(int x) {
	for (int i = x; i < M; i += lowbit(i)) T[i]--;
}
int getsum(int x) {
	int ret = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		ret += T[i];
	}
	return ret;
}

int query(int l, int r) {
	return getsum(r) - getsum(l - 1);
}
void solve() {
	scanf("%d", &n);
	int cnt = 0;
	for (int i = 0; i < M; i++) T[i] = 0;
	
	memset(occur, 0, sizeof occur);
	
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &a[i], &b[i], &c[i]);
		if (!occur[a[i]]) {
			add(a[i]);
			ans++;
			occur[a[i]] = 1;
		}
		
		event[++cnt] = make_pair(make_pair(b[i], 1), i);
		event[++cnt] = make_pair(make_pair(c[i], 0), i);
	}

	
	sort(event + 1, event + cnt + 1);
	
	for (int i = 1; i <= cnt; i++) {
		int id = event[i].second;
		if (event[i].first.second == 0) {
			int sum = query(b[id], c[id]);
			if (!sum) {
				ans++;
				add(c[id]);
			}
			else {
				if (sum == 1 && a[id] >= b[id] && a[id] <= c[id]) {
					ans++;
					add(c[id]);
				}
			}
		}
	}
	
	printf("%d\n", ans);
}

int main() {
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++) {
		printf("Case #%d: ",tt);
		solve();
	}
	return 0;
}
